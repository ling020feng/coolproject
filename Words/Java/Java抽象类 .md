抽象类  /基类/父类

1、无法实例化

被abstract修饰的为抽象类

abstract class animal{

​     //动物名字

​     String name;

​     //动物叫声

​     public void shout(){

​     System.out.println("叫声...");



};

class Dog extends animal{

​     //狗类独有的方法

​     public void guard(){

​          System.out.println("狗有看门的独特本领！");

​     }

};

不能使用

animal aaa = new animal(); //错误的



animal aaa = new Dog() ; //这个就是对的

但是只能调用抽象类里面的方法！！！

比如 

```
aaa.shout(); //能够编译通过

aaa.guard(); //不能够编译通过,这个会报错
```

dog ddd = new Dog(); //它就可以调用抽象类和子类的所有方法





很常见的例子：

```
        List list;//正确，list = null;        List list = new List();//是错误的用法
        List list = new ArrayList();//常见用法
```

使用ArrayList 含有List没有的方法

也可以直接 ArrayList list = new ArrayList();



**平常为什么不直接用** ArrayList list 而喜欢用List list 去定义呢？

问题就在于List接口有多个实现类，现在你用的是ArrayList，也许哪一天你需要换成其它的实现类，如 

LinkedList或者Vector等等，这时你只要改变这一行就行了： List list = new LinkedList(); 其它使用了list地方的代码根本不需要改动。 

​       假设你开始用ArrayList alist = new ArrayList(), 这下有的改了，特别是如果你使用了ArrayList实现类特有的方法和属性。

这样的好处是为了代码的可维护性，可复用性，可扩展性以及灵活性