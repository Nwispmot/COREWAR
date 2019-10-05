.name   "Sylvester Stallone"
.comment "The world ain't all sunshine and rainbows.
It's a very mean and nasty place and I don't care how tough you are it will beat you to your knees and keep you there permanently if you let it.
You, me, or nobody is gonna hit as hard as life. But it ain't about how hard ya hit. It's about how hard you can get hit and keep moving forward.
How much you can take and keep moving forward. That's how winning is done!"
fork1:		live	%42
fork2:		live	%42
			fork	%:leon
			ldi 	%-5,r3,r1
			sti 	r1,%17,r3
			add 	r3,r4,r3
			xor 	r5,r3,r6
			zjmp	%:fork1
			ld		%0,r7
live0:		live 	%66
live1:		live 	%66
live2:		live 	%66
live3:		live	%66
live4:		live 	%66
			zjmp 	%:leon_live
fork3:		live	%42
			fork	%:roger
			ld		%0,r15	
			zjmp	%:roger_live
			ldi 	%-5,r3,r1
			sti 	r1,%17,r3
			add 	r3,r4,r3
			xor	 	r5,r3,r6
			zjmp 	%:roger_live
			ld		%0,r7
			zjmp 	%:fork1
leon:		ld      %0,r2
leon_live:	live    %42
			ldi     %:leon,r2,r3
			sti     r3,r8,r2
			add     r2,r4,r2
			xor     r13,r2,r7
			zjmp    %415
			ld      %0,r15
roger:		ld		%0,r10
roger_live:	live	%42
			ldi		%:roger,r10,r11
			sti		r11,r12,r10
			add		r10,r4,r10
			xor		r6,r10,r7
			zjmp	%-361
			ld		%0,r7
			zjmp	%:roger
			ld		%0,r15
			sti 	r1,%:live0,%1
			sti 	r1,%:live1,%1
			sti 	r1,%:live2,%1
			sti 	r1,%:live3,%1
			sti	 	r1,%:live4,%1


