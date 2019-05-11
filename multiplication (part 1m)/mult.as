	lw	0	0	zero
	lw	0	1	init	store result
	lw	0	2	mcand
	lw	0	3	mplier
	lw	0	4	index	store index  (0000100 for example)
	lw	0	5	large	store 1000 0000 0000 0000
	lw	0	6	zero	store mplier & index
	lw	0	7	one	store one
loop	nor	3	3	3	invert mplier
	nor	4	4	4	invert index
	nor	3	4	6	calculate mplier & index
	nor	3	3	3	restore mplier
	nor	4	4	4	restore index
	beq	0	6	here	if mplier & index != 0, do PC+1, else to here
	add	2	1	1	add mcand to result
here	add	4	4	4	left shift the index
	add	2	2	2	double the mcand
	beq	4	5	done	stop the program if index == largest
	beq	0	0	loop
done	halt
mcand	.fill	32766
mplier	.fill	10383
index	.fill	1
zero	.fill	0
one	.fill	1
init	.fill	0
large	.fill	32768
