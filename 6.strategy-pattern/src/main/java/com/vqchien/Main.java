package com.vqchien;

public class Main {
  public static void main(String args[]) {
    Duck mallardDuck = new MallardDuck();
    System.out.println(mallardDuck.display());
    System.out.println(mallardDuck.performFly());
    System.out.println(mallardDuck.performQuack());

    Duck rubberDuck = new RubberDuck();
    System.out.println(rubberDuck.display());
    System.out.println(rubberDuck.performFly());
    System.out.println(rubberDuck.performQuack());
  }
}
