.name  "Tadara"

.comment "Fighting!"

    live %66
	st r6,-4
live:	ld %0,r7
	zjmp %456
		zjmp %-207
		sti r2,%:live0,%1
    	sti r3,%:live1,%1
    	sti r4,%:live2,%1
    	sti r5,%:live3,%1
    	sti r6,%:live4,%1
    live0:	live %66
    live1:	live %66
    live2:	live %66
    live3:	live %66
    live4:	live %66
	zjmp %:live0
	xor r3,r3,r3
	sti r7,%:live,%1
