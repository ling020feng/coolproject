# grep



​	

```
[root@www ~]# grep [-acinv] [--color=auto] '搜寻字符串' filename
选项与参数：
-a ：将 binary 文件以 text 文件的方式搜寻数据
-c ：计算找到 '搜寻字符串' 的次数
-i ：忽略大小写的不同，所以大小写视为相同
-n ：顺便输出行号
-v ：反向选择，亦即显示出没有 '搜寻字符串' 内容的那一行！
--color=auto ：可以将找到的关键词部分加上颜色的显示喔！
```

```
grep -v root /etc/passwd | grep -v nologin  
就像一个多层滤网，一个grep滤掉一个杂质。
```

#### 正则表达式

- 字符类的反向选择 [^] ：

```
'[^a-z]oo' 、'[^g]oo'
[root@www ~]# grep -n '[^g]oo' regular_express.txt
2:apple is my favorite food.
3:Football game is not use feet only.

```

- 定位

  - 出现在首列：[^] (在括号外)：

    ```
    '^the'、'^[a-z]'出现在首列的是小写字母、'^[^a-zA-Z]'出现在首列的不是字母
    [root@www ~]# grep -n '^the' regular_express.txt
    12:the symbol '*' is represented as start.
    ```

    

    

  - 出现在尾列：$

```
找出空白，只有开头和结尾：'^$'
[root@www ~]# grep -n '^$' regular_express.txt
22:
以小数点结尾的哪行（小数点要用转义字符）：'\.$'
```

- 任意字节与重复字节

  ```
  . (小数点)：代表『一定有一个任意字节』的意思；（一个点就是一个，两个点就是两个）
  * (星号)：代表『重复前一个字符， 0 到无穷多次』的意思，为组合形态
  
  [root@www ~]# grep -n 'g..d' regular_express.txt
  1:"Open Source" is a good mechanism to develop programs.
  9:Oh! The soup taste good.
  16:The world <Happy> is the same with "glad".
  
  当我们需要『至少两个 o 以上的字串』时，就需要 ooo* ，亦即是：
  ```