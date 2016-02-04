Unfortunately most of the really nice icons are copyrighted.

What you can do is grab pictures from:
	http://www.iconusa.com/online/D&D_index.htm
	http://www.wizards.com/default.asp?x=dnd/mix/gallery
	http://www.wpclipart.com/animals

A really quick way of getting all the icon images is to go to one of
the above URLs, copy the URL of the icon set you want. Use 'wget' to
grab the page plus all the images/icons. There is wget for Windows XP etc,
just google for it. Then from a temporary directory run "wget URL" to
get them all. The move them to the appropriate icon directory. If you
do it for all the sets, you should have about 900 icons to use.

The program can use both gif & png icon files. If you want to be nice
then grab them, trim the edges and convert them to PNG files.

The best sizes for charactor icons are 32x32 but monsters look
very nice in 64x64 or 128x128

To convert them under Linux, I do:

for i in `ls *.jpg`
do
	F=`echo "$i" | tr '[A-Z]' '[a-z]' | sed "s/\.[A-z][A-z][A-z]/.png/"`
	convert -resize 64x64 $i $F
done
