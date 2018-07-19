	.file	"main.c"
 # GNU C11 (x86_64-win32-seh-rev1, Built by MinGW-W64 project) version 7.2.0 (x86_64-w64-mingw32)
 #	compiled by GNU C version 7.2.0, GMP version 6.1.2, MPFR version 3.1.6, MPC version 1.0.3, isl version isl-0.18-GMP

 # GGC heuristics: --param ggc-min-expand=100 --param ggc-min-heapsize=131072
 # options passed: 
 # -iprefix D:/perso/otherDevsProject/DEV/Ressources/Compilers/GCC/mingw64/bin/../lib/gcc/x86_64-w64-mingw32/7.2.0/
 # -U_REENTRANT main.c -mtune=core2 -march=nocona -O3 -Os -Wall -Wextra
 # -Wpedantic -Wno-format-nonliteral -Wshadow -Werror -ansi -std=c11
 # -fverbose-asm -fno-stack-protector
 # options enabled:  -faggressive-loop-optimizations -falign-labels
 # -fasynchronous-unwind-tables -fauto-inc-dec -fbranch-count-reg
 # -fcaller-saves -fchkp-check-incomplete-type -fchkp-check-read
 # -fchkp-check-write -fchkp-instrument-calls -fchkp-narrow-bounds
 # -fchkp-optimize -fchkp-store-bounds -fchkp-use-static-bounds
 # -fchkp-use-static-const-bounds -fchkp-use-wrappers -fcode-hoisting
 # -fcombine-stack-adjustments -fcommon -fcompare-elim -fcprop-registers
 # -fcrossjumping -fcse-follow-jumps -fdefer-pop
 # -fdelete-null-pointer-checks -fdevirtualize -fdevirtualize-speculatively
 # -fdwarf2-cfi-asm -fearly-inlining -feliminate-unused-debug-types
 # -fexpensive-optimizations -fforward-propagate -ffp-int-builtin-inexact
 # -ffunction-cse -fgcse -fgcse-lm -fgnu-runtime -fgnu-unique
 # -fguess-branch-probability -fhoist-adjacent-loads -fident
 # -fif-conversion -fif-conversion2 -findirect-inlining -finline
 # -finline-atomics -finline-functions -finline-functions-called-once
 # -finline-small-functions -fipa-bit-cp -fipa-cp -fipa-icf
 # -fipa-icf-functions -fipa-icf-variables -fipa-profile -fipa-pure-const
 # -fipa-ra -fipa-reference -fipa-sra -fipa-vrp -fira-hoist-pressure
 # -fira-share-save-slots -fira-share-spill-slots
 # -fisolate-erroneous-paths-dereference -fivopts -fkeep-inline-dllexport
 # -fkeep-static-consts -fleading-underscore -flifetime-dse -flra-remat
 # -flto-odr-type-merging -fmath-errno -fmerge-constants
 # -fmerge-debug-strings -fmove-loop-invariants -fomit-frame-pointer
 # -foptimize-sibling-calls -fpartial-inlining -fpeephole -fpeephole2 -fpic
 # -fplt -fprefetch-loop-arrays -free -freg-struct-return -freorder-blocks
 # -freorder-functions -frerun-cse-after-loop
 # -fsched-critical-path-heuristic -fsched-dep-count-heuristic
 # -fsched-group-heuristic -fsched-interblock -fsched-last-insn-heuristic
 # -fsched-rank-heuristic -fsched-spec -fsched-spec-insn-heuristic
 # -fsched-stalled-insns-dep -fschedule-fusion -fschedule-insns2
 # -fsemantic-interposition -fset-stack-executable -fshow-column
 # -fshrink-wrap -fshrink-wrap-separate -fsigned-zeros
 # -fsplit-ivs-in-unroller -fsplit-wide-types -fssa-backprop -fssa-phiopt
 # -fstdarg-opt -fstore-merging -fstrict-aliasing -fstrict-overflow
 # -fstrict-volatile-bitfields -fsync-libcalls -fthread-jumps
 # -ftoplevel-reorder -ftrapping-math -ftree-bit-ccp
 # -ftree-builtin-call-dce -ftree-ccp -ftree-ch -ftree-coalesce-vars
 # -ftree-copy-prop -ftree-cselim -ftree-dce -ftree-dominator-opts
 # -ftree-dse -ftree-forwprop -ftree-fre -ftree-loop-if-convert
 # -ftree-loop-im -ftree-loop-ivcanon -ftree-loop-optimize
 # -ftree-parallelize-loops= -ftree-phiprop -ftree-pre -ftree-pta
 # -ftree-reassoc -ftree-scev-cprop -ftree-sink -ftree-slsr -ftree-sra
 # -ftree-switch-conversion -ftree-tail-merge -ftree-ter -ftree-vrp
 # -funit-at-a-time -funwind-tables -fverbose-asm -fzero-initialized-in-bss
 # -m128bit-long-double -m64 -m80387 -maccumulate-outgoing-args
 # -malign-double -malign-stringops -mcx16 -mfancy-math-387 -mfentry
 # -mfp-ret-in-387 -mfxsr -mieee-fp -mlong-double-80 -mmmx -mms-bitfields
 # -mno-sse4 -mpush-args -mred-zone -msse -msse2 -msse3 -mstack-arg-probe
 # -mstackrealign -mvzeroupper

	.text
	.globl	VertexArray_t_push
	.def	VertexArray_t_push;	.scl	2;	.type	32;	.endef
	.seh_proc	VertexArray_t_push
VertexArray_t_push:
	pushq	%rbx	 #
	.seh_pushreg	%rbx
	subq	$48, %rsp	 #,
	.seh_stackalloc	48
	.seh_endprologue
 # main.c:28:   realloc(self->array, sizeof(self->array) + sizeof(el));
	movl	$12, %edx	 #,
 # main.c:26: void VertexArray_t_push(struct VertexArray_t *self, GLfloat el) {
	movq	%rcx, %rbx	 # self, self
 # main.c:28:   realloc(self->array, sizeof(self->array) + sizeof(el));
	movq	24(%rcx), %rcx	 # self_10(D)->array, self_10(D)->array
 # main.c:26: void VertexArray_t_push(struct VertexArray_t *self, GLfloat el) {
	movss	%xmm1, 44(%rsp)	 # el, %sfp
 # main.c:28:   realloc(self->array, sizeof(self->array) + sizeof(el));
	call	realloc	 #
 # main.c:30:   self->array[self->length] = el;
	movq	(%rbx), %rax	 # self_10(D)->length, _3
	movq	24(%rbx), %rdx	 # self_10(D)->array, self_10(D)->array
	movss	44(%rsp), %xmm1	 # %sfp, el
	movss	%xmm1, (%rdx,%rax,4)	 # el, *_5
 # main.c:31:   self->length += 1;
	incq	%rax	 # tmp99
 # main.c:32:   self->sizeOfItems += sizeof(el);
	addq	$4, 16(%rbx)	 #, self_10(D)->sizeOfItems
 # main.c:31:   self->length += 1;
	movq	%rax, (%rbx)	 # tmp99, self_10(D)->length
 # main.c:33:   self->sizeOfStructure = sizeof(el);
	movq	$4, 8(%rbx)	 #, self_10(D)->sizeOfStructure
 # main.c:35: }
	addq	$48, %rsp	 #,
	popq	%rbx	 #
	ret
	.seh_endproc
	.globl	VertexArray_t_initArray
	.def	VertexArray_t_initArray;	.scl	2;	.type	32;	.endef
	.seh_proc	VertexArray_t_initArray
VertexArray_t_initArray:
	pushq	%rbx	 #
	.seh_pushreg	%rbx
	subq	$32, %rsp	 #,
	.seh_stackalloc	32
	.seh_endprologue
 # main.c:36: void VertexArray_t_initArray(struct VertexArray_t *self, size_t size) {
	movq	%rcx, %rbx	 # self, self
 # main.c:37:   self->length = size;
	movq	%rdx, (%rcx)	 # size, self_4(D)->length
 # main.c:38:   self->array = malloc(size * sizeof(float));
	leaq	0(,%rdx,4), %rcx	 #, tmp91
	call	malloc	 #
 # main.c:39:   self->sizeOfItems = sizeof(self->array);
	movq	$8, 16(%rbx)	 #, self_4(D)->sizeOfItems
 # main.c:38:   self->array = malloc(size * sizeof(float));
	movq	%rax, 24(%rbx)	 # tmp92, self_4(D)->array
 # main.c:40:   self->sizeOfStructure = sizeof(*self);
	movq	$32, 8(%rbx)	 #, self_4(D)->sizeOfStructure
 # main.c:42: }
	addq	$32, %rsp	 #,
	popq	%rbx	 #
	ret
	.seh_endproc
	.globl	VertexArray_t_freeIt
	.def	VertexArray_t_freeIt;	.scl	2;	.type	32;	.endef
	.seh_proc	VertexArray_t_freeIt
VertexArray_t_freeIt:
	pushq	%rbx	 #
	.seh_pushreg	%rbx
	subq	$32, %rsp	 #,
	.seh_stackalloc	32
	.seh_endprologue
 # main.c:44: void VertexArray_t_freeIt(struct VertexArray_t *self) {
	movq	%rcx, %rbx	 # self, self
 # main.c:45:   free(self->array);
	movq	24(%rcx), %rcx	 # self_3(D)->array, self_3(D)->array
	call	free	 #
 # main.c:46:   self->length = 0;
	movq	$0, (%rbx)	 #, self_3(D)->length
 # main.c:47:   self->sizeOfItems = sizeof(self->length) + sizeof(self->sizeOfItems);
	movq	$16, 16(%rbx)	 #, self_3(D)->sizeOfItems
 # main.c:49: }
	addq	$32, %rsp	 #,
	popq	%rbx	 #
	ret
	.seh_endproc
	.globl	ArrayOfVertex_t_push
	.def	ArrayOfVertex_t_push;	.scl	2;	.type	32;	.endef
	.seh_proc	ArrayOfVertex_t_push
ArrayOfVertex_t_push:
	pushq	%r13	 #
	.seh_pushreg	%r13
	pushq	%r12	 #
	.seh_pushreg	%r12
	pushq	%rbp	 #
	.seh_pushreg	%rbp
	pushq	%rdi	 #
	.seh_pushreg	%rdi
	pushq	%rsi	 #
	.seh_pushreg	%rsi
	pushq	%rbx	 #
	.seh_pushreg	%rbx
	subq	$40, %rsp	 #,
	.seh_stackalloc	40
	.seh_endprologue
 # main.c:51: void ArrayOfVertex_t_push(struct ArrayOfVertex_t *self, struct VertexArray_t *verArr_s) {
	movq	%rcx, %rbx	 # self, self
 # main.c:53:   realloc(self->VertexArray_s, sizeof(self->VertexArray_s) + sizeof(*verArr_s));
	movq	24(%rcx), %rcx	 # self_22(D)->VertexArray_s, self_22(D)->VertexArray_s
 # main.c:51: void ArrayOfVertex_t_push(struct ArrayOfVertex_t *self, struct VertexArray_t *verArr_s) {
	movq	%rdx, %rbp	 # verArr_s, verArr_s
 # main.c:53:   realloc(self->VertexArray_s, sizeof(self->VertexArray_s) + sizeof(*verArr_s));
	movl	$40, %edx	 #,
 # main.c:57:   self->VertexArray_s[self->length] = *verArr_s;
	movq	%rbp, %rsi	 # verArr_s, verArr_s
 # main.c:53:   realloc(self->VertexArray_s, sizeof(self->VertexArray_s) + sizeof(*verArr_s));
	call	realloc	 #
 # main.c:57:   self->VertexArray_s[self->length] = *verArr_s;
	movq	(%rbx), %r13	 # self_22(D)->length, _3
	movl	$8, %ecx	 #, tmp137
	movq	%r13, %r12	 # _3, tmp133
	salq	$5, %r12	 #, tmp133
	addq	24(%rbx), %r12	 # self_22(D)->VertexArray_s, _5
	movq	%r12, %rdi	 # _5, _5
	rep movsl
 # main.c:62:   self->VertexArray_s[self->length].array = malloc(*verArr_s->array);
	movq	24(%rbp), %rax	 # verArr_s_24(D)->array, verArr_s_24(D)->array
	movss	(%rax), %xmm0	 # *_6, *_6
	ucomiss	.LC0(%rip), %xmm0	 #, *_6
	jnb	.L5	 #,
	cvttss2siq	%xmm0, %rcx	 # *_6, tmp139
	jmp	.L6	 #
.L5:
	subss	.LC0(%rip), %xmm0	 #, tmp142
	movabsq	$-9223372036854775808, %rax	 #, tmp145
	cvttss2siq	%xmm0, %rcx	 # tmp142, tmp139
	xorq	%rax, %rcx	 # tmp145, tmp139
.L6:
	call	malloc	 #
	movq	0(%rbp), %rdx	 # verArr_s_24(D)->length, verArr_s_24(D)->length
	movq	%rax, 24(%r12)	 # _9, _5->array
	leaq	-4(,%rdx,4), %rdx	 #, ivtmp.28
.L7:
 # main.c:65:   for (size_t i = verArr_s->length; i-- > 0;) {
	cmpq	$-4, %rdx	 #, ivtmp.28
	je	.L10	 #,
 # main.c:66:     self->VertexArray_s[self->length].array[i] = verArr_s->array[i];
	movq	24(%rbp), %rcx	 # verArr_s_24(D)->array, verArr_s_24(D)->array
	movss	(%rcx,%rdx), %xmm0	 # *_12, _14
	movss	%xmm0, (%rax,%rdx)	 # _14, MEM[base: _9, index: ivtmp.28_36, offset: 0B]
	subq	$4, %rdx	 #, ivtmp.28
	jmp	.L7	 #
.L10:
 # main.c:76:   self->sizeOfItems += verArr_s->sizeOfStructure;
	movq	8(%rbp), %rax	 # verArr_s_24(D)->sizeOfStructure, verArr_s_24(D)->sizeOfStructure
 # main.c:70:   self->length += 1;
	incq	%r13	 # tmp150
 # main.c:76:   self->sizeOfItems += verArr_s->sizeOfStructure;
	addq	%rax, 16(%rbx)	 # verArr_s_24(D)->sizeOfStructure, self_22(D)->sizeOfItems
 # main.c:70:   self->length += 1;
	movq	%r13, (%rbx)	 # tmp150, self_22(D)->length
 # main.c:78: }
	addq	$40, %rsp	 #,
	popq	%rbx	 #
	popq	%rsi	 #
	popq	%rdi	 #
	popq	%rbp	 #
	popq	%r12	 #
	popq	%r13	 #
	ret
	.seh_endproc
	.globl	ArrayOfVertex_t_initArray
	.def	ArrayOfVertex_t_initArray;	.scl	2;	.type	32;	.endef
	.seh_proc	ArrayOfVertex_t_initArray
ArrayOfVertex_t_initArray:
	pushq	%rsi	 #
	.seh_pushreg	%rsi
	pushq	%rbx	 #
	.seh_pushreg	%rbx
	subq	$40, %rsp	 #,
	.seh_stackalloc	40
	.seh_endprologue
 # main.c:80: void ArrayOfVertex_t_initArray(struct ArrayOfVertex_t *self, size_t size) {
	movq	%rcx, %rbx	 # self, self
 # main.c:81:   self->VertexArray_s = malloc(size * sizeof(VertexArray_t));
	movq	%rdx, %rcx	 # size, tmp91
 # main.c:80: void ArrayOfVertex_t_initArray(struct ArrayOfVertex_t *self, size_t size) {
	movq	%rdx, %rsi	 # size, size
 # main.c:81:   self->VertexArray_s = malloc(size * sizeof(VertexArray_t));
	salq	$5, %rcx	 #, tmp91
	call	malloc	 #
 # main.c:82:   self->length = size;
	movq	%rsi, (%rbx)	 # size, self_6(D)->length
 # main.c:81:   self->VertexArray_s = malloc(size * sizeof(VertexArray_t));
	movq	%rax, 24(%rbx)	 # tmp92, self_6(D)->VertexArray_s
 # main.c:83:   self->sizeOfItems = sizeof(*self);
	movq	$32, 16(%rbx)	 #, self_6(D)->sizeOfItems
 # main.c:85: }
	addq	$40, %rsp	 #,
	popq	%rbx	 #
	popq	%rsi	 #
	ret
	.seh_endproc
	.globl	newVector
	.def	newVector;	.scl	2;	.type	32;	.endef
	.seh_proc	newVector
newVector:
	pushq	%rsi	 #
	.seh_pushreg	%rsi
	pushq	%rbx	 #
	.seh_pushreg	%rbx
	subq	$40, %rsp	 #,
	.seh_stackalloc	40
	.seh_endprologue
 # main.c:92: struct Vector *newVector (size_t sz) {
	movq	%rcx, %rsi	 # sz, sz
 # main.c:95:     struct Vector *retVal = malloc (sizeof (struct Vector));
	movl	$16, %ecx	 #,
	call	malloc	 #
 # main.c:96:     if (retVal == NULL)
	testq	%rax, %rax	 # <retval>
 # main.c:95:     struct Vector *retVal = malloc (sizeof (struct Vector));
	movq	%rax, %rbx	 #, <retval>
 # main.c:96:     if (retVal == NULL)
	je	.L12	 #,
 # main.c:101:     retVal->data = malloc (sz * sizeof (double));
	leaq	0(,%rsi,8), %rcx	 #, tmp92
	call	malloc	 #
 # main.c:102:     if (retVal->data == NULL) {
	testq	%rax, %rax	 # tmp93
 # main.c:101:     retVal->data = malloc (sz * sizeof (double));
	movq	%rax, (%rbx)	 # tmp93, retVal_7->data
 # main.c:102:     if (retVal->data == NULL) {
	jne	.L14	 #,
 # main.c:103:         free (retVal);
	movq	%rbx, %rcx	 # <retval>,
 # main.c:104:         return NULL;
	xorl	%ebx, %ebx	 # <retval>
 # main.c:103:         free (retVal);
	call	free	 #
 # main.c:104:         return NULL;
	jmp	.L12	 #
.L14:
 # main.c:109:     retVal->size = sz;
	movq	%rsi, 8(%rbx)	 # sz, retVal_7->size
.L12:
 # main.c:111: }
	movq	%rbx, %rax	 # <retval>,
	addq	$40, %rsp	 #,
	popq	%rbx	 #
	popq	%rsi	 #
	ret
	.seh_endproc
	.globl	delVector
	.def	delVector;	.scl	2;	.type	32;	.endef
	.seh_proc	delVector
delVector:
	pushq	%rbx	 #
	.seh_pushreg	%rbx
	subq	$32, %rsp	 #,
	.seh_stackalloc	32
	.seh_endprologue
 # main.c:116:     if (vector != NULL) {
	testq	%rcx, %rcx	 # vector
 # main.c:113: void delVector (struct Vector *vector) {
	movq	%rcx, %rbx	 # vector, vector
 # main.c:116:     if (vector != NULL) {
	je	.L18	 #,
 # main.c:117:         free (vector->data);
	movq	(%rcx), %rcx	 # vector_3(D)->data,
	call	free	 #
 # main.c:118:         free (vector);
	movq	%rbx, %rcx	 # vector,
 # main.c:120: }
	addq	$32, %rsp	 #,
	popq	%rbx	 #
 # main.c:118:         free (vector);
	jmp	free	 #
.L18:
 # main.c:120: }
	addq	$32, %rsp	 #,
	popq	%rbx	 #
	ret
	.seh_endproc
	.def	__main;	.scl	2;	.type	32;	.endef
	.section .rdata,"dr"
.LC1:
	.ascii "INIT !\0"
.LC2:
	.ascii "Starting of the program, start_t = %ld\12\0"
.LC4:
	.ascii "End of the big loop, end_t = %ld\12\0"
.LC6:
	.ascii "Total time taken by CPU: %ld\12\0"
.LC7:
	.ascii "yolo !\0"
.LC8:
	.ascii "testArrayOfGLfloatArrStruct.VertexArray_s[0].array[0] %f\12\0"
.LC9:
	.ascii "testArrayOfGLfloatArrStruct.VertexArray_s[0].array[1] %f\12\0"
.LC10:
	.ascii "testArrayOfGLfloatArrStruct.VertexArray_s[0].array[2] %f\12\0"
.LC11:
	.ascii "yolo \12\0"
	.section	.text.startup,"x"
	.globl	main
	.def	main;	.scl	2;	.type	32;	.endef
	.seh_proc	main
main:
	pushq	%rbp	 #
	.seh_pushreg	%rbp
	pushq	%rdi	 #
	.seh_pushreg	%rdi
	pushq	%rsi	 #
	.seh_pushreg	%rsi
	pushq	%rbx	 #
	.seh_pushreg	%rbx
	subq	$104, %rsp	 #,
	.seh_stackalloc	104
	.seh_endprologue
 # main.c:133:   printf("Starting of the program, start_t = %ld\n", start_t);
	movl	$7000, %ebx	 #, ivtmp_16
 # main.c:122: int main() {
	call	__main	 #
 # main.c:125:   VertexArray_t_initArray(&testGLfloatArrStruct, 0);
	leaq	32(%rsp), %rsi	 #, tmp107
 # main.c:123:   printf("INIT !\n");
	leaq	.LC1(%rip), %rcx	 #,
	call	puts	 #
 # main.c:128:   ArrayOfVertex_t_initArray(&testArrayOfGLfloatArrStruct, 0);
	leaq	64(%rsp), %rdi	 #, tmp108
 # main.c:125:   VertexArray_t_initArray(&testGLfloatArrStruct, 0);
	xorl	%edx, %edx	 #
	movq	%rsi, %rcx	 # tmp107,
	call	VertexArray_t_initArray	 #
 # main.c:128:   ArrayOfVertex_t_initArray(&testArrayOfGLfloatArrStruct, 0);
	xorl	%edx, %edx	 #
	movq	%rdi, %rcx	 # tmp108,
	call	ArrayOfVertex_t_initArray	 #
 # main.c:132:   start_t = clock();
	call	clock	 #
 # main.c:133:   printf("Starting of the program, start_t = %ld\n", start_t);
	leaq	.LC2(%rip), %rcx	 #,
	movl	%eax, %edx	 # start_t,
 # main.c:132:   start_t = clock();
	movl	%eax, %ebp	 #, start_t
 # main.c:133:   printf("Starting of the program, start_t = %ld\n", start_t);
	call	printf	 #
.L21:
 # main.c:135:     VertexArray_t_push(&testGLfloatArrStruct, 654646.56f);
	movss	.LC3(%rip), %xmm1	 #,
	movq	%rsi, %rcx	 # tmp107,
	call	VertexArray_t_push	 #
 # main.c:134:   for (size_t i = 0; i < 7000; i++) {
	decq	%rbx	 # ivtmp_16
	jne	.L21	 #,
 # main.c:137:   end_t = clock();
	call	clock	 #
 # main.c:138:   printf("End of the big loop, end_t = %ld\n", end_t);
	leaq	.LC4(%rip), %rcx	 #,
 # main.c:137:   end_t = clock();
	movl	%eax, %ebx	 #, end_t
 # main.c:138:   printf("End of the big loop, end_t = %ld\n", end_t);
	movl	%eax, %edx	 # end_t,
	call	printf	 #
 # main.c:141:   printf("Total time taken by CPU: %ld\n", total_t);
	leaq	.LC6(%rip), %rcx	 #,
 # main.c:140:   total_t = (double)(end_t - start_t) / CLOCKS_PER_SEC;
	subl	%ebp, %ebx	 # start_t, tmp110
	cvtsi2sd	%ebx, %xmm0	 # tmp110, tmp111
	divsd	.LC5(%rip), %xmm0	 #, tmp112
	cvttsd2si	%xmm0, %edx	 # tmp112, total_t
 # main.c:141:   printf("Total time taken by CPU: %ld\n", total_t);
	call	printf	 #
 # main.c:155:   printf("yolo !\n");
	leaq	.LC7(%rip), %rcx	 #,
	call	puts	 #
 # main.c:156:   ArrayOfVertex_t_push(&testArrayOfGLfloatArrStruct, &testGLfloatArrStruct);
	movq	%rsi, %rdx	 # tmp107,
	movq	%rdi, %rcx	 # tmp108,
	call	ArrayOfVertex_t_push	 #
 # main.c:157:   printf("yolo !\n");
	leaq	.LC7(%rip), %rcx	 #,
	call	puts	 #
 # main.c:158:   VertexArray_t_freeIt(&testGLfloatArrStruct);
	movq	%rsi, %rcx	 # tmp107,
	call	VertexArray_t_freeIt	 #
 # main.c:160:   printf("testArrayOfGLfloatArrStruct.VertexArray_s[0].array[0] %f\n", testArrayOfGLfloatArrStruct.VertexArray_s[0].array[0]);
	movq	88(%rsp), %rax	 # testArrayOfGLfloatArrStruct.VertexArray_s, testArrayOfGLfloatArrStruct.VertexArray_s
	leaq	.LC8(%rip), %rcx	 #,
	movq	24(%rax), %rax	 # _4->array, _4->array
	cvtss2sd	(%rax), %xmm0	 # *_5, tmp120
	movapd	%xmm0, %xmm1	 # tmp120,
	movq	%xmm0, %rdx	 # tmp120,
	call	printf	 #
 # main.c:161:   printf("testArrayOfGLfloatArrStruct.VertexArray_s[0].array[1] %f\n", testArrayOfGLfloatArrStruct.VertexArray_s[0].array[1]);
	movq	88(%rsp), %rax	 # testArrayOfGLfloatArrStruct.VertexArray_s, testArrayOfGLfloatArrStruct.VertexArray_s
	leaq	.LC9(%rip), %rcx	 #,
	movq	24(%rax), %rax	 # _8->array, _8->array
	cvtss2sd	4(%rax), %xmm0	 # MEM[(GLfloat *)_9 + 4B], tmp128
	movapd	%xmm0, %xmm1	 # tmp128,
	movq	%xmm0, %rdx	 # tmp128,
	call	printf	 #
 # main.c:162:   printf("testArrayOfGLfloatArrStruct.VertexArray_s[0].array[2] %f\n", testArrayOfGLfloatArrStruct.VertexArray_s[0].array[2]);
	movq	88(%rsp), %rax	 # testArrayOfGLfloatArrStruct.VertexArray_s, testArrayOfGLfloatArrStruct.VertexArray_s
	leaq	.LC10(%rip), %rcx	 #,
	movq	24(%rax), %rax	 # _12->array, _12->array
	cvtss2sd	8(%rax), %xmm0	 # MEM[(GLfloat *)_13 + 8B], tmp136
	movapd	%xmm0, %xmm1	 # tmp136,
	movq	%xmm0, %rdx	 # tmp136,
	call	printf	 #
 # main.c:164:   printf("yolo !\n");
	leaq	.LC7(%rip), %rcx	 #,
	call	puts	 #
 # main.c:165:   scanf("yolo \n");
	leaq	.LC11(%rip), %rcx	 #,
	call	scanf	 #
 # main.c:167: }
	xorl	%eax, %eax	 #
	addq	$104, %rsp	 #,
	popq	%rbx	 #
	popq	%rsi	 #
	popq	%rdi	 #
	popq	%rbp	 #
	ret
	.seh_endproc
	.section .rdata,"dr"
	.align 4
.LC0:
	.long	1593835520
	.align 4
.LC3:
	.long	1226822505
	.align 8
.LC5:
	.long	0
	.long	1083129856
	.ident	"GCC: (x86_64-win32-seh-rev1, Built by MinGW-W64 project) 7.2.0"
	.def	realloc;	.scl	2;	.type	32;	.endef
	.def	malloc;	.scl	2;	.type	32;	.endef
	.def	free;	.scl	2;	.type	32;	.endef
	.def	puts;	.scl	2;	.type	32;	.endef
	.def	clock;	.scl	2;	.type	32;	.endef
	.def	printf;	.scl	2;	.type	32;	.endef
	.def	scanf;	.scl	2;	.type	32;	.endef
