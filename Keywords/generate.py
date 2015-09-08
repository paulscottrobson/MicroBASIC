#
#	Generate include file
#
print("/* This code is automatically generated */\n")
current = 128
keywordList = []
lines = open("keywords.txt").readlines()
lines = [x.replace("\t"," ").strip().upper() for x in lines if x.strip() != ""]
print("#define KEYWORD_BASE ("+str(current)+")")
print("")
for l in lines:
	if l[0] == '[':
		if l[1] == '/':
			print("#define KGROUP_END_"+l[2:-1]+" ("+str(current-1)+")")
			print("")
		else:
			print("#define KGROUP_START_"+l[1:-1]+" ("+str(current)+")")
	else:
		keyword = l[:l.find(" ")].strip()
		keywordList.append('"'+keyword+'"')
		print("#define KWD_"+l[len(keyword):].strip()+" ("+str(current)+")")
		current = current + 1

print("#define KEYWORD_END ("+str(current)+")")
print("")
keywordList.append('""')
print("#ifdef INCLUDE_STATIC_KEYWORD_LIST")
print("static char * _keywords[] = { "+",".join(keywordList)+" };")
print("#endif")