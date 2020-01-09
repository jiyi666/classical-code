package com.example.javatestlib1;

/** 地址类:实现Cloneable接口，覆写clone方法 */
class Address implements Cloneable{
    public Address(String adr) {
        this.adr = adr;
    }

    public String getAdr() {
        return adr;
    }

    public void setAdr(String adr) {
        this.adr = adr;
    }

    @Override
    protected Address clone() throws CloneNotSupportedException{
        return (Address) super.clone();
    }
    private String adr;
}

/** 学生类：两个成员变量，一个String，一个是类“地址” */
class Student implements Cloneable{
    public Student(){

    }
    public Student(String name, Address address) {
        this.name = name;
        this.address = address;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public Address getAddress() {
        return address;
    }

    public void setAddress(Address address) {
        this.address = address;
    }

    @Override
    public Student clone() throws CloneNotSupportedException{
        Student clone = (Student)super.clone();
        clone.address = (Address)address.clone();
        return clone;
    }
    private String name;
    private Address address;

}
public class test {
    public static void main(String[] args) throws CloneNotSupportedException{
        Student std = new Student();
        std.setName("张三");
        std.setAddress(new Address("四川"));

        Student cloneStd = std.clone();
        cloneStd.setName("李四");
        cloneStd.getAddress().setAdr("河北");

        System.out.println("name:" + std.getName() + ", addr:" + std.getAddress().getAdr());
        System.out.println("name1:" + cloneStd.getName() + ", addr1:" + cloneStd.getAddress().getAdr());


    }
}
