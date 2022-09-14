tr -cd 'A-Z''a-z''\0''\n' < dirtyData/wlist_match1.txt > dirtyData/wlist_match1_try2.txt
tr -s '\n' < dirtyData/wlist_match1_try2.txt > dirtyData/wlist_match1_try2_rmln.txt
awk 'length <= 15' dirtyData/wlist_match1_try2_rmln.txt > dirtyData/wlist_match1_try2_rmln_try2.txt
awk 'length > 2' dirtyData/wlist_match1_try2_rmln_try2.txt > dirtyData/wlist_match1_try2_rmln.txt
sort -u dirtyData/wlist_match1_try2_rmln.txt > final.txt
shuf final.txt > clean.txt

rm final.txt
rm dirtyData/wlist_match1_try2.txt
rm dirtyData/wlist_match1_try2_rmln.txt
rm dirtyData/wlist_match1_try2_rmln_try2.txt