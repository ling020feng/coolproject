# Git使用
标签:Git

# 查看分支
```
//查看本地分支
git branch 


//查看本地和远程分支
git branch -a
```

# 创建分支与切换分支
```
//创建本地分支
git branch <local_branch_name>

//切换到本地分支(存在的前提下)
git checkout <local_branch_name>

//创建并切换本地分支
git checkout -b <local_branch_name>

//推送到同名远程分支(没有的话会自动创建同名远程分支)
git push origin <remote_branch_name>

//推送指定本地分支到指定远程分支
git push origin <local_branch_name>:<remote_branch_name>

//将本地分支与远程分支建立关联并推送
git push -u origin <local_branch_name>:<remote_branch_name>

//将远程分支映射到本地命名为local-branchname  的一分支
git checkout -b local-branchname origin/remote_branchname 

//强制推送
git push -f
```

# 本地分支添加索引
```
//添加指定文件至该分支索引
git add <file_name>

//添加所有新增文件至该分支索引
git add --all
```

# 本地提交   
```
//提交指定文件至本地分支
git commit -m "commit info" <file_name>

//提交所有修文件至本地分支
git commit -am "commit info"
```

# 远程分支推送
```
//将本地分支推送到远程分支上
git push
```

# 查看本地分支状态
```
//查看当前本地分支的状态(修改文件)
git status

//查看当前文件与上个版本的差异
git diff <file_name>
```

# 查看版本变更信息
```
//查看所有版本信息(时间,提交者,版本号,版本信息)
git log

//查看所有版本的信息包括修改的文件和行数
git log --stat

//查看该版本的修改详情
git log -p commit_code

//查看该文件的修改历史
git log -p file_name
```

# 查看本地历史git操作记录
```
//查看本地历史git操作记录
git relog
```

# 撤销修改
```
对于文件 myfile.txt

① 修改后 未add（添加到暂存区） 需要撤销修改时：
        git checkout -- myfile.txt 或 手动删除工作区修改
        工作区 ： clean  暂存区： clean
② 修改后 add了（未commit） 再次修改文件  要撤销第二次修改时：
        git checkout -- myfile.txt (将暂存区恢复到工作区)
        暂存区有第一次的修改需要commit
③ 修改后 add了（未commit），需要撤销修改时：
        git reset HEAD myfile.txt (将暂存区修改删除)
        此时工作区的修改还未撤销
        git checkout -- myfile.txt (撤销工作区修改)
④ 修改后 add并commit了，需要撤销修改时：
        git reset --hard HEAD^  (版本回退)**


```

# 分支操作

```
//合并分之
git merge <name> //合并某分之到当前分之(实际就是将当前分之的指针指向某分之)

//创建分之
git branch <name>

//切换分之
git checkout <name>

//创建+切换分之
git checkout -b <name>

//删除分之(已经合并或者提交)
git branch -d <name>

//强行删除分之
git branch -D <name>


```

# 开发的同时修改bug
dev上开发时，需要修复master上的bug，使用`git stash` 保存dev现场后切换至master修复bug，修复完成后，为了保证dev上的相同bug被修复，需要将master合并至dev上：`checkout dev`切换回dev分支，`git merge master`合并master至dev上，则dev上已经修复的bug会被同步至dev上;然后刚才工作现场存到哪去了？用`git stash list`命令看看;用`git stash pop`恢复，恢复的同时把stash内容也删了：


# 本地分之关联到远程分之
git pull提示“no tracking information”，则说明本地分支和远程分支的链接关系没有创建，用命令`git branch --set-upstream branch-name origin/branch-name`

# 标签

```
//新建一个标签,默认是HEAD,也可以指定一个commit id;
git tag <name>

//指定标签信息
git tag -a <tagname> -m "blablabla..."

git tag -s <tagname> -m "blablabla..."可以用PGP签名标签；

//查看所有标签
git tag

//推送本地标签
git push origin <tagname>

//推送全部本地标签
git push origin --tags

//删除本地标签
git tag -d <tagname>

//删除远程标签
git push origin :refs/tags/<tagname>
```



