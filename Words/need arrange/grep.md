### grep(egrep)：用来在文本文件中查找一个特定的字符串

+ egrep用的是扩展的正则表达式
  	grep  options "正则表达式"  files
  		options:
  			-n  显示行号
  			-E  egrep
  			-i  ignore 在字符串比较时忽略大小写
  			-# 表示同时显示匹配行的上下#行号
  			-c count打印每个文件里匹配行的个数
  			--color=always
              --color=never
              --color=auto
              -H  显示文件名
              -h  不显示文件名
  				

	eg: grep -n -E --color=always -H "[0-9]+" 1.txt
	    grep -n -E --color=always -H "([0-9]{1,3}\.){3}[0-9]{1,3}" IP.txt