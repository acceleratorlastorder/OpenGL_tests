document.addEventListener("DOMContentLoaded", function(event) {
  console.log("DOM fully loaded and parsed");
  main_Init();
});

function main_Init() {
  loadProgram();
};

function contextProgram(canvasId) {
  this.GL = null;
  this.rendering_ctx = {
    shaderProgram: null,
    vertexShader: {
      isInited: false,
      value: null
    },
    fragmentShader: {
      isInited: false,
      value: null
    },
    shouldStop: false
  };
  this.getContext = function() {
    let canvas = document.getElementById(canvasId);
    this.GL = canvas.getContext('webgl2');
    let isWebGL2 = !!this.GL;
    if (!isWebGL2) { // try to fallback to webgl 1
      this.GL = canvas.getContext('webgl') ||
        canvas.getContext('experimental-webgl');
      console.warn("got fallback context: ", this.GL);
    }
    if (!this.GL) {
      console.log('your browser does not support WebGL');
      return false;
    }
    console.log("canvas inited");
    return true;
  };

  /**
   * [Compiling the given vertex shader onto the GPU]
   * @param  {[type]} fileContent   [description]
   * @return {[type]}       [description]
   */
  this.loadVertexShader = function(fileContent) {

    this.rendering_ctx.vertexShader.value = this.createShader(this.GL, fileContent, this.GL.VERTEX_SHADER);
    if (!this.rendering_ctx.vertexShader.value) {
      console.error("loadVertexShader() error");
      return;
    }

    this.GL.attachShader(this.rendering_ctx.shaderProgram, this.rendering_ctx.vertexShader.value);

    this.rendering_ctx.vertexShader.isInited = true;
  };

  this.createShader = function(gl, sourceCode, type) {
    // Compiles either a shader of type gl.VERTEX_SHADER or gl.FRAGMENT_SHADER
    var shader = gl.createShader(type);
    gl.shaderSource(shader, sourceCode);
    gl.compileShader(shader);

    if (!gl.getShaderParameter(shader, gl.COMPILE_STATUS)) {
      var info = gl.getShaderInfoLog(shader);
      console.error("Could not compile WebGL program. \n\n", info);
      return null;
    }
    return shader;
  }

  /**
   * [Compiling the given fragment shader onto the GPU]
   * @param  {[type]} fileContent   [description]
   * @return {[type]}       [description]
   */
  this.loadFragmentShader = function(fileContent) {

    this.rendering_ctx.fragmentShader.value = this.createShader(this.GL, fileContent, this.GL.FRAGMENT_SHADER);
    if (!this.rendering_ctx.fragmentShader.value) {
      console.error("loadFragmentShader() error");
      return;
    }

    this.GL.attachShader(this.rendering_ctx.shaderProgram, this.rendering_ctx.fragmentShader.value);

    this.rendering_ctx.fragmentShader.isInited = true;
  };

  /**
   * [description]
   * @return {[type]} [description]
   */
  this.loadShaders = async function() {
    var fileContent = "";
    let filePath = "./shaders/vertexShader.glsl";

    this.rendering_ctx.shaderProgram = this.GL.createProgram();
    // get vertex shader file
    fileContent = await readFile(filePath);
    this.loadVertexShader(fileContent);

    /* maybe workaround to use this since it's cleaner and more generic
    this.createShader(this.GL, fileContent, this.GL.VERTEX_SHADER)
    */
    fileContent = "";
    // get fragment shader file
    filePath = "./shaders/fragmentShader.frag";
    //printf("fileContent: %s\n", filePath);
    fileContent = await readFile(filePath);
    this.loadFragmentShader(fileContent);

    this.linkshaderProgram();

    this.setVertexShaderAttributes();
    return;
  };

  this.linkshaderProgram = function() {
    this.GL.linkProgram(this.rendering_ctx.shaderProgram);
    if (!this.GL.getProgramParameter(this.rendering_ctx.shaderProgram, this.GL.LINK_STATUS)) {
      var info = this.GL.getProgramInfoLog(this.rendering_ctx.shaderProgram);
      console.error('Could not link WebGL program. \n\n' + info);
    }

    this.GL.useProgram(this.rendering_ctx.shaderProgram);

    return this.rendering_ctx.shaderProgram;
  };

  this.setVertexShaderAttributes = function() {
    this.rendering_ctx.posAttrib = this.GL.getAttribLocation(this.rendering_ctx.shaderProgram, "position");
    this.GL.vertexAttribPointer(this.rendering_ctx.posAttrib, 2, this.GL.FLOAT, this.GL.FALSE, 0, 0);
    this.GL.enableVertexAttribArray(this.rendering_ctx.posAttrib);
  };

  this.uploadVertexOntoTheGPU = function() {
    let vertices = [
      0.0, 0.5, // Vertex 1 (X, Y)
      0.5, -0.5, // Vertex 2 (X, Y)
      -0.5, -0.5 // Vertex 3 (X, Y)
    ];

    this.rendering_ctx.srcData = new Float32Array(vertices);
    this.rendering_ctx.vbufferObj = [];
    this.rendering_ctx.vbufferObj = this.GL.createBuffer();
    console.log("vbufferObj: ", this.rendering_ctx.vbufferObj);

    this.GL.bindBuffer(this.GL.ARRAY_BUFFER, this.rendering_ctx.vbufferObj); // BIND current vbo as array buffer
    // and make it current active
    // arrayBuff
    this.GL.bufferData(this.GL.ARRAY_BUFFER, this.rendering_ctx.srcData, this.GL.STATIC_DRAW);
    console.log("vbufferObj finished");
    return this.rendering_ctx.vbufferObj;
  };

  this.loadObject = async function() {
    this.rendering_ctx.vao;
    this.rendering_ctx.vao = this.GL.createVertexArray();
    this.GL.bindVertexArray(this.rendering_ctx.vao);

    this.uploadVertexOntoTheGPU();

    await this.loadShaders();

    return;
  };


  this.mainLoop = function() {
    var self = this;
    setInterval(function() {
      self.GL.enable(self.GL.DEPTH_TEST);
      // Set clear color to black, fully opaque
      self.GL.clearColor(0.0, 0.0, 0.0, 1.0);
      // Clear the color buffer with specified clear color
      self.GL.clear(self.GL.COLOR_BUFFER_BIT);

      self.GL.drawArrays(self.GL.TRIANGLES, 0, 3);

    }, 20);
  };

  this.startRendering = function() {
    this.mainLoop();
  };

  this.loadScene = async function() {
    await this.loadObject();
    await this.startRendering();
  };

  this.bootProgram = function() {
    if (this.getContext()) {
      this.loadScene();
    } else {
      console.error("can't boot the context");
    }
  };
};

/**
 * [readFile description]
 * @param  {[String]} path          [description]
 * @return {[String]}               [return the response as string]
 */
async function readFile(path) {
  return await new Promise(resolve => {
    var oReq = new XMLHttpRequest();

    oReq.addEventListener("progress", updateProgress);
    oReq.addEventListener("load", transferComplete);
    oReq.addEventListener("error", transferFailed);
    oReq.addEventListener("abort", transferCanceled);
    oReq.overrideMimeType("text/plain");

    // progress on transfers from the server to the client (downloads)
    function updateProgress(oEvent) {
      if (oEvent.lengthComputable) {
        var percentComplete = oEvent.loaded / oEvent.total * 100;
        console.log("loading percentCompleted: ", percentComplete);
      } else {
        // Unable to compute progress information since the total size is unknown
        console.log("can't get computable length");
        return;
      }
    };

    function transferComplete(evt) {
      console.log("The transfer is complete.");
      resolve(oReq.response);
      return;
    };

    function transferFailed(evt) {
      console.log("An error occurred while transferring the file.");
      resolve(undefined);
      return;
    };

    function transferCanceled(evt) {
      console.log("The transfer has been canceled by the user.");
      resolve(undefined);
      return;
    };

    oReq.open("GET", path);
    oReq.send();
  });
};


function loadProgram() {
  let canvasProgram = new contextProgram("canvas");
  canvasProgram.bootProgram();
};
