package com.example.javatestlib;

import java.util.Random;

/** 抽象中介者 */
abstract class AbstractMediator {
    protected Purchase purchase;
    protected Sale sale;
    protected Stock stock;

    public AbstractMediator(){
        purchase = new Purchase(this);
        sale = new Sale(this);
        stock = new Stock(this);
    }
    /* 中介者最重要的方法叫做事件方法， 处理多个对象之间的关系 */
    public abstract void execute(String str,Object...objects);
}

/** 具体中介者 */
class Mediator extends AbstractMediator {
    //中介者最重要的方法
    public void execute(String str,Object...objects){
        if(str.equals("purchase.buy")){
            this.buyComputer((Integer)objects[0]);
        }else if(str.equals("sale.sell")){
            this.sellComputer((Integer)objects[0]);
        }else if(str.equals("sale.offsell")){
            this.offSell();
        }else if(str.equals("stock.clear")){
            this.clearStock();
        }
    }
    /* 采购电脑 */
    private void buyComputer(int number){
        int saleStatus = super.sale.getSaleStatus();
        if(saleStatus>80){ //销售情况良好
            System.out.println("采购IBM电脑:"+number + "台");
            super.stock.increase(number);
        }else{ //销售情况不好
            int buyNumber = number/2; //折半采购
            System.out.println("采购IBM电脑： "+buyNumber+ "台");
        }
    }
    /* 销售电脑 */
    private void sellComputer(int number){
        if(super.stock.getStockNumber()<number){ //库存数量不够销售
            super.purchase.buyIBMcomputer(number);
        }
        super.stock.decrease(number);
    }
    /* 折价销售电脑 */
    private void offSell(){
        System.out.println("折价销售IBM电脑"+stock.getStockNumber()+"台");
    }
    /* 清仓处理 */
    private void clearStock(){

        super.sale.offSale();
        super.purchase.refuseBuyIBM();
    }
}

/** 抽象同事类 */
abstract class AbstractColleague {
    protected AbstractMediator mediator;

    public AbstractColleague(AbstractMediator mediator){
        this.mediator = mediator;
    }
}

/** 采购管理 */
class Purchase extends AbstractColleague{
    public Purchase(AbstractMediator mediator){
        super(mediator);
    }
    /* 采购IBM电脑 */
    public void buyIBMcomputer(int number){
        super.mediator.execute("purchase.buy", number);
    }
    /* 不再采购IBM电脑 */
    public void refuseBuyIBM(){
        System.out.println("不再采购IBM电脑");
    }
}

/** 库存管理 */
class Stock extends AbstractColleague {
    public Stock(AbstractMediator _mediator){
        super(_mediator);
    }
    /* 刚开始有100台电脑 */
    private static int COMPUTER_NUMBER =100;
    /* 库存增加 */
    public void increase(int number){
        COMPUTER_NUMBER = COMPUTER_NUMBER + number;
        System.out.println("库存数量为： "+COMPUTER_NUMBER);
    }
    /* 库存降低 */
    public void decrease(int number){
        COMPUTER_NUMBER = COMPUTER_NUMBER - number;
        System.out.println("库存数量为： "+COMPUTER_NUMBER);
    }
    /* 获得库存数量 */
    public int getStockNumber(){
        return COMPUTER_NUMBER;
    }
    /* 存货压力大了， 就要通知采购人员不要采购， 销售人员要尽快销售 */
    public void clearStock(){
        System.out.println("清理存货数量为： "+COMPUTER_NUMBER);
        super.mediator.execute("stock.clear");
    }
}

/** 销售管理 */
class Sale extends AbstractColleague {
    public Sale(AbstractMediator mediator){
        super(mediator);
    }
    //销售IBM电脑
    public void sellIBMComputer(int number){
        super.mediator.execute("sale.sell", number);
        System.out.println("销售IBM电脑"+number+"台");
    }
    //反馈销售情况， 0～100变化， 0代表根本就没人买， 100代表非常畅销， 出一个卖一个
    public int getSaleStatus(){
        Random rand = new Random(System.currentTimeMillis());
        int saleStatus = rand.nextInt(100);
        System.out.println("IBM电脑的销售情况为： "+saleStatus);
        return saleStatus;
    }
    //折价处理
    public void offSale(){
        super.mediator.execute("sale.offsell");
    }
}

public class MediatorDesign {
    public static void main(String[] args) {
        AbstractMediator mediator = new Mediator();
        //采购人员采购电脑
        System.out.println("------采购人员采购电脑--------");
        Purchase purchase = new Purchase(mediator);
        purchase.buyIBMcomputer(100);
        //销售人员销售电脑
        System.out.println("\n------销售人员销售电脑--------");
        Sale sale = new Sale(mediator);
        sale.sellIBMComputer(1);
        //库房管理人员管理库存
        System.out.println("\n------库房管理人员清库处理--------");
        Stock stock = new Stock(mediator);
        stock.clearStock();
    }
}
