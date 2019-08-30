[Android 消息框显示](https://www.cnblogs.com/GnagWang/archive/2010/11/26/1888762.html)

默认的格式：

```
Toast.makeText(getApplicationContext(), "默认Toast样式",
     Toast.LENGTH_SHORT).show();
```

这个是在底部显示“”里的消息；



```
toast = Toast.makeText(getApplicationContext(),
     "自定义位置Toast", Toast.LENGTH_LONG);
   toast.setGravity(Gravity.CENTER, 0, 0);
   toast.show();
```

这个自定义显示消息位置在屏幕中间



可以插图片显示



来自其他线程显示