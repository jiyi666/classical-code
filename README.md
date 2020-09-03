# classical-code


#java
1.threaddemo:线程的基本操作；
2.threadsyncdemo:线程的同步操作演示；
3.threadtostop：线程的停止方法；

#C++
1.circlebuff：使用C++实现环形buffer的操作；
2.binder： Android中binder通信实现的最简demo;
3.anonymity_binder:在binder实例的基础上，将demo修改为binder demo；

#C
1.二级指针与数组的结合：使用二级指针与数组结合；

2.callback:回调函数的典型使用，callback.h是回调函数的挂钩，callback.c是调用者，main.c是被调用者；
编译指令为：gcc -I ./ main.c callback.c -o test

3.sem+task:采用信号量与线程的方式灵活控制任务的执行次数；
编译指令为：gcc -I ./ main.c com_task.c -o test -lpthread