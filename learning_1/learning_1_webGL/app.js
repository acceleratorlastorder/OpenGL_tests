document.addEventListener("DOMContentLoaded", function(event) {
  console.log("DOM fully loaded and parsed");
  main_Init();
});

function main_Init() {
  loadProgram();
}

function contextProgram(canvasId) {
  this.gl = null;
  this.getContext = function() {
    let canvas = document.getElementById(canvasId);
    this.gl = canvas.getContext('webgl2');
    let isWebGL2 = !!this.gl;
    if (!isWebGL2) { // try to fallback to webgl 1
      this.gl = canvas.getContext('webgl') ||
        canvas.getContext('experimental-webgl');
    }
    if (!this.gl) {
      console.log('your browser does not support WebGL');
      return false;
    }
    console.log("canvas inited");
    return true;
  }

  this.mainLoop = function() {
    // Set clear color to black, fully opaque
    this.gl.clearColor(0.0, 0.0, 0.0, 1.0);
    // Clear the color buffer with specified clear color
    this.gl.clear(this.gl.COLOR_BUFFER_BIT);
  }

  this.bootProgram = function() {
    if (this.getContext()) {
      this.mainLoop();
    }else {
      console.error("can't boot the context");
    }
  }
}



function loadProgram() {
  let canvasProgram = new contextProgram("canvas");
  canvasProgram.bootProgram();
}
