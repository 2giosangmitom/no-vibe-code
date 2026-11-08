package com.vqchien;

public class Main {
  public static void main(String args[]) {
    Duck mallardDuck = new MallardDuck();
    System.out.println(mallardDuck.display());
    System.out.println(mallardDuck.performFly());
    System.out.println(mallardDuck.performQuack());
  }
}
