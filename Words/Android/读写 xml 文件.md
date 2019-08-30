开发的时候，老是会遇到这种情况，自定义的全局变量，在退出应用时候，被释放掉了

当再次使用的时候，会出现null错误或者读到不想要的值

这时候可以使用把数据写到xml文件中保存，操作如下：

**读xml文件**

```java

private void readRegisterState()
{
    Context context = this;
    SharedPreferences sp = context.getSharedPreferences("fenceData", Context.MODE_PRIVATE);// 从“fenceIData”的xml文件去读数据，权限为私有（仅软件使用）
    infenceId = sp.getLong("inFenceId", 1);//第二个参数为默认值 第一个参数为你写的时候设定的名字
}
```

**写xml文件**

```java
    
    public void latRegisterStateWrite(){
    SharedPreferences sf;    //定义类型
    Context context = this;
    sf = context.getSharedPreferences("fenceData", Context.MODE_PRIVATE); // 写到 fenceData.xml文件
    SharedPreferences.Editor editor = sf.edit();                          // 定义一个类型框接收                  
    editor.putLong("inFenceId",1L);     // 输送 前面为名字 后面为值
    editor.commit();
}
```

`