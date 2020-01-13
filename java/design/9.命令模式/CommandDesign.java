package com.example.javatestlib;

/** 抽象组 */
abstract class Group {
    //甲乙双方分开办公， 如果你要和某个组讨论， 你首先要找到这个组
    public abstract void find();
    //被要求增加功能
    public abstract void add();
    //被要求删除功能
    public abstract void delete();
    //被要求修改功能
    public abstract void change();
    //被要求给出所有的变更计划
    public abstract void plan();
}

/** 需求组 */
class RequirementGroup extends Group {

    public void find() {
        System.out.println("找到需求组...");
    }

    public void add() {
        System.out.println("客户要求增加一项需求...");
    }

    public void change() {
        System.out.println("客户要求修改一项需求...");
    }

    public void delete() {
        System.out.println("客户要求删除一项需求...");
    }

    public void plan() {
        System.out.println("客户要求需求变更计划...");
    }
}

/** 美工组 */
class PageGroup extends Group {

    public void find() {
        System.out.println("找到美工组...");
    }

    public void add() {
        System.out.println("客户要求增加一个页面...");
    }

    public void change() {
        System.out.println("客户要求修改一个页面...");
    }

    public void delete() {
        System.out.println("客户要求删除一个页面...");
    }

    public void plan() {
        System.out.println("客户要求页面变更计划...");
    }
}

/** 代码组 */
class CodeGroup extends Group {
    //客户要求代码组过去和他们谈
    public void find() {
        System.out.println("找到代码组...");
    }

    public void add() {
        System.out.println("客户要求增加一项功能...");
    }

    public void change() {
        System.out.println("客户要求修改一项功能...");
    }

    public void delete() {
        System.out.println("客户要求删除一项功能...");
    }

    public void plan() {
        System.out.println("客户要求代码变更计划...");
    }
}

/** 命令抽象类 */
abstract class Command {
    /* 把三个组都定义好， 子类可以直接使用 */
    protected RequirementGroup rg = new RequirementGroup(); //需求组
    protected PageGroup pg = new PageGroup(); //美工组
    protected CodeGroup cg = new CodeGroup(); //代码组

    public abstract void execute();
}

/** 命令具体类：增加需求类 */
class AddRequirementCommand extends Command {
    public void execute() {
        super.rg.find();
        super.rg.add();
        super.rg.plan();
    }
}

/** 命令具体类：删除页面类 */
class DeletePageCommand extends Command {
    public void execute() {
        super.pg.find();
        super.rg.delete();
        super.rg.plan();
    }
}

/** 负责人invoker */
class Invoker {
    /* 管理命令 */
    private Command command;
    /* 客户发出的命令 */
    public void setCommand(Command command){
        this.command = command;
    }
    /* 执行客户的命令 */
    public void action(){
        this.command.execute();
    }
}



public class CommandDesign {
    public static void main(String[] args) {

        Invoker xiaoSan = new Invoker();

        System.out.println("------------客户要求增加一项需求---------------");

        Command command = new AddRequirementCommand();

        xiaoSan.setCommand(command);

        xiaoSan.action();
    }
}
