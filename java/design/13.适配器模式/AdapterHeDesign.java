package com.example.javatestlib1;

import java.util.HashMap;
import java.util.Map;

/** 员工信息接口 */
interface IUserInfo {
    //获得用户姓名
    public String getUserName();
    //获得家庭地址
    public String getHomeAddress();
    //手机号码， 这个太重要， 手机泛滥呀
    public String getMobileNumber();
    //办公电话， 一般是座机
    public String getOfficeTelNumber();
    //这个人的职位是什么
    public String getJobPosition();
    //获得家庭电话， 这有点不好， 我不喜欢打家庭电话讨论工作
    public String getHomeTelNumber();
}

/** 员工信息实现类 */
class UserInfo implements IUserInfo {
    /*
     * 获得家庭地址， 下属送礼也可以找到地方
     */
    public String getHomeAddress() {
        System.out.println("这里是员工的家庭地址...");
        return null;
    }
    /** 获得家庭电话号码 */
    public String getHomeTelNumber() {
        System.out.println("员工的家庭电话是...");
        return null;
    }
    /** 员工的职位， 是部门经理还是普通职员 */
    public String getJobPosition() {
        System.out.println("这个人的职位是BOSS...");
        return null;
    }
    /** 手机号码 */
    public String getMobileNumber() {
        System.out.println("这个人的手机号码是0000...");
        return null;
    }
    /** 办公室电话， 烦躁的时候最好"不小心"把电话线踢掉 */
    public String getOfficeTelNumber() {
        System.out.println("办公室电话是...");
        return null;
    }
    /** 姓名， 这个很重要 */
    public String getUserName() {System.out.println("姓名叫做...");
        return null;
    }
}


/** 外包员工基本信息接口 */
interface IOuterUserBaseInfo {
    //基本信息， 比如名称、 性别、 手机号码等
    public Map getUserBaseInfo();
}
/** 外包员工基本信息实现类 */
class OuterUserBaseInfo implements IOuterUserBaseInfo {
    /*
     * 用户的基本信息
     */
    public Map getUserBaseInfo() {
        HashMap baseInfoMap = new HashMap();
        baseInfoMap.put("userName", "这个员工叫混世魔王...");
        baseInfoMap.put("mobileNumber", "这个员工电话是...");
        return baseInfoMap;
    }
}

/** 外包员工家庭信息接口 */
interface IOuterUserHomeInfo {
    //用户的家庭信息
    public Map getUserHomeInfo();
}
/** 外包员工家庭信息实现类 */
class OuterUserHomeInfo implements IOuterUserHomeInfo {
    /*
     * 员工的家庭信息
     */
    public Map getUserHomeInfo() {
        HashMap homeInfo = new HashMap();
        homeInfo.put("homeTelNumbner", "员工的家庭电话是...");
        homeInfo.put("homeAddress", "员工的家庭地址是...");
        return homeInfo;
    }
}
/** 外包员工工作信息接口 */
interface IOuterUserOfficeInfo {
    //工作区域信息
    public Map getUserOfficeInfo();
}
/** 外包员工工作信息实现类 */
class OuterUserOfficeInfo implements IOuterUserOfficeInfo {
    /*
     * 员工的工作信息， 比如， 职位等
     */
    public Map getUserOfficeInfo() {
        HashMap officeInfo = new HashMap();
        officeInfo.put("jobPosition","这个人的职位是BOSS...");
        officeInfo.put("officeTelNumber", "员工的办公电话是...");
        return officeInfo;
    }
}


/** 适配器 */
class OuterUserInfo implements IUserInfo {
    //源目标对象
    private IOuterUserBaseInfo baseInfo = null; //员工的基本信息
    private IOuterUserHomeInfo homeInfo = null; //员工的家庭信息
    private IOuterUserOfficeInfo officeInfo = null; //工作信息
    //数据处理
    private Map baseMap = null;
    private Map homeMap = null;
    private Map officeMap = null;
    //构造函数传递对象
    public OuterUserInfo(IOuterUserBaseInfo baseInfo,IOuterUserHomeInfo homeInfo, IOuterUserOfficeInfo officeInfo){
        this.baseInfo = baseInfo;
        this.homeInfo = homeInfo;
        this.officeInfo = officeInfo;
        //数据处理
        this.baseMap = this.baseInfo.getUserBaseInfo();
        this.homeMap = this.homeInfo.getUserHomeInfo();
        this.officeMap = this.officeInfo.getUserOfficeInfo();
    }
    //家庭地址
    public String getHomeAddress() {
        String homeAddress = (String)this.homeMap.get("homeAddress");
        System.out.println(homeAddress);
        return homeAddress;
    }
    //家庭电话号码
    public String getHomeTelNumber() {
        String homeTelNumber = (String)this.homeMap.get("homeTelNumber");
        System.out.println(homeTelNumber);
        return homeTelNumber;
    }
    //职位信息
    public String getJobPosition() {
        String jobPosition = (String)this.officeMap.get("jobPosition");
        System.out.println(jobPosition);
        return jobPosition;
        }
    //手机号码
    public String getMobileNumber() {
        String mobileNumber = (String)this.baseMap.get("mobileNumber");
        System.out.println(mobileNumber);
        return mobileNumber;
        }
    //办公电话
    public String getOfficeTelNumber() {
        String officeTelNumber= (String)this.officeMap.get("officeTelNumber");
        System.out.println(officeTelNumber);
        return officeTelNumber;
    }
    // 员工的名称
    public String getUserName() {
        String userName = (String)this.baseMap.get("userName");
        System.out.println(userName);
        return userName;
    }
}

public class AdapterHeDesign {
    public static void main(String[] args) {
        //外系统的人员信息
        IOuterUserBaseInfo baseInfo = new OuterUserBaseInfo();
        IOuterUserHomeInfo homeInfo = new OuterUserHomeInfo();
        IOuterUserOfficeInfo officeInfo = new OuterUserOfficeInfo();
        //传递三个对象
        IUserInfo youngGirl = new OuterUserInfo(baseInfo,homeInfo,officeInfo);
        //从数据库中查到10个
        for(int i=0;i<10;i++){
            youngGirl.getMobileNumber();
        }
    }
}
