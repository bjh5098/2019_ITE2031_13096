	lw	0	1	pos1
	lw	0	3	B
	nor	0	3	5	lw data hazard must stall
	lw	0	2	A
	add	2	5	4	lw data hazard must stall
	add	4	1	4	data hazard needs forwarding
check	beq	4	6	done	consecutive beq
	add	1	6	6
	beq	0	0	check	branch is always taken
done	halt
A	.fill	31
B	.fill	27
pos1	.fill	1
