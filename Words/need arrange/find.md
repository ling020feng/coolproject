### find - search for files in a directory hierarchy	

find用于在一个目录下递归查找文件
用法：
	find [path...] [options]
		options	
			-name pattern 文件名通配符，*代表0个或多个任意字符,?代表一个字符
			-type b,c,d,p,f,l,s
				b:block 块设备
				c:char 字符设备
				d: dir 目录
				p: pipe管道文件
				f: regular file普通文件
				l: link 符号链接文件
				s: socket 套接字文件
			-size n
			-perm mode 权限精确匹配,用八进制,如0777
				-mode 要求所有权限位都匹配
				/mode 只要求匹配一位就可以了
			-newer file  比file更新
			-amin  n :file was last accessed n minutes ago
			-atime n :file was last accessed n*24 hours ago
			-cmin  n :file was last changed  n minutes ago
			-ctime n :file was last changed  n*24 hours ago	
			-mmin  n: file's data(文件内容)was  last modified  n minutes ago
			-mtime n: file's data(文件内容)was last modified n*24 hours ago
			-delete  删除找到的文件
			-exec  command  {} \;  {}代表找到的文件名
				==>找到一个文件，就执行一次command命令
			
			