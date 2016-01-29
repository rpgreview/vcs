#!/bin/sh
#########################################

cd srd/monsters/cf

#for i in CELESTIAL_DINOSAUR.html
for i in `ls CEL*html FIE*html`
do
	lynx -dump $i | grep -v "^$" | sed 's/^   //' | sed 's/\[.\]//g' | sed 's/\[..\]//g' | sed 's/\^B//g' | sed 's/damage resistance/damage reduction/' | awk '
BEGIN {
        getline;
        printf "%s\n", $0;
        FS=":";
}

{
        if (NF > 1) { printf "\n%s\n", $0; } else { printf "%s ", $0; }
}' > /var/tmp/$$.txt

	awk '
BEGIN {
	getline;
	printf "name %s\n", tolower($0);
	getline;
}
{
	if ($0 == "Hit Dice:") { getline; printf "hit_dice %s\n", $0; }
	else if ($0 == "Initiative:") { getline; printf "initiative %s\n", $0; }
	else if ($0 == "Speed:") { getline; printf "speed %s\n", $0; }
	else if ($0 == "Armor Class:") { getline; printf "armor_class %s\n", $0; }
	else if ($0 == "Full Attack:") { getline; printf "full_attack %s\n", $0; }
	else if ($0 == "Space/Reach:") { getline; split($0, ln, "/"); printf "space %d\nreach %d\n", ln[1], ln[2]; }
	else if ($0 == "Saves:") { getline; sq = 0; printf "\nsaves %s\n", $0; }
	else if ($0 == "Abilities:") { getline; printf "abilities %s\n", $0; }
	else if ($0 == "Skills:") { getline; printf "skills %s\n", $0; }
	else if ($0 == "Feats:") { getline; printf "feats %s\n", $0; }
	else if ($0 == "Environment:") { getline; printf "environment %s\n", $0; }
	else if ($0 == "Special Qualities:") { sq = 1; getline; printf "special_qualities %s", $0; }
	else if ($0 == "Challenge Rating:") { getline; printf "challenge_rating %s\n", $0; }
	else if ($0 == "dice") { getline; printf "dice %s\n", $0; }
	else { if (sq == 1) printf " %s", $0; }
}' /var/tmp/$$.txt > /var/tmp/$$.$$

	NC=`grep full_attack /var/tmp/$$.$$ | wc -l`
	if [ $NC -eq 1 ]
	then
		cat /var/tmp/$$.$$
	fi
done
