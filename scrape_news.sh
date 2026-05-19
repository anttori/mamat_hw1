#!/bin/bash

link="https://www.ynetnews.com/category/3082"

# get ynet home page using given link
home_page=$(wget --no-check-certificate -O - $link 2>/dev/null)

# save links to other articles from home page
articles=$(grep -oP "https://(www.)?ynetnews.com/article/[a-zA-Z0-9]*" <<< "$home_page" | sort | uniq)

# print articles count
echo "$(echo "$articles" | wc -l)"

for article in $articles; do   # loop for each article

	# save article text
	data=$(wget --no-check-certificate -O - $article 2>/dev/null)
	echo -n "$article" 	# print article link
	
	# check if arctile text contains at least one name
	if [[ $(grep -oP "Netanyahu|Gantz|Bennett|Peretz" <<< "$data" | wc -l) -gt 0 ]]; then
		
		# for each politician name in a article 
		for name in Netanyahu Gantz Bennett Peretz; do

			# name occurences count 
			count=$(grep -o $name <<< "$data" | wc -l)
		
			# print name with occurence count or - if count is zero
			echo -n ", $name, $count"
		done
		
		echo ""
		
	else
		
		echo ", -"	# print - if there are no names in this article
		
	fi
		
done



