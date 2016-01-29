
Welcome to VCS-ADMP, a AD&D DM Program. This is a combat program for AD&D v3.5. 
It is not a character generator or a campaign program ... just combat.

By: Torquil Gault copyright 2005+, email torquilgault@yahoo.com,
    Portions copyright Wizards of the Coast (see the Open Gaming Licence)

	This program will be updated on this site:
		http://www.geocities.com/SiliconValley/Peaks/7843/

This program will not do everything, AD&D is too complicated for that but I've
tried to go for the 80/20 Rule ... 80% of the rules for 20% of the effort.
So, I'm lazy ... sue me ;)

But, realistically, it should handle most of the 'things' you want it to.
Things like Prayer and Bless spells can be 'done' in the Adjustments tab.
Automatic damage can be done in the "Auto-Damage" tab (in Other) for things
like Acid Arrow etc that do damage for a number of rounds.

Compiling the Source Requirements:
	A good C compiler ... gcc or the like
	FLTK 1.1.x (http://www.fltk.org). Please review fltk-changes.txt
	
	You can use MinGW (http://www.mingw.org) to compile it in Windows

	If you make changes using 'fluid' (the FLTK GUI program) then run
	the 'fix' program.

Please read the "help.txt" on how to use this program.

If you make changes or find a bug please email the details so that I
can update the main source code.

Or if there is a feature you'd like added, email me and I'll see what I can do.

To start with your own data, just remove the player.* & monst.* files and
then start the program. Once you've added all your player's details, you 
should press "Save All" button in the System tab. You should review the System
settings to ensure they are what you want. You may also want to press the "Reset
for a new Combat" button so that everthing is nicely reset ready for the first combat.

*** You should always do that "Save All" step before you exit the program ***

Note, doing a "Save All" will also save the notes.

If you want to do standard groups of monsters ie. Ogre war-band, then do the following:
	Remove all monsters in the Other tab
	Add all the monsters in the Edit tab
	Save the monster file as "ogre-wb" in the System tab

	When you want to use those monsters, load that file in the System tab.

	If you want it to roll their HP based on the HitDice of the monster, select that action
	in the Other tab (in Other).

If you download a HTML version of the SRD and put in the "srd" subdirectory, you will be able to view it within ADMP.

The one that I use is:
		http://www.systemreferencedocuments.org/35/stephenh.zip                   or
		http://www.darkshire.net/~jhkim/rpg/srd/srd_revised_html/v35SRD_html.zip
