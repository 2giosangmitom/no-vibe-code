package com.vqchien;

import com.vqchien.behaviors.FlyWithWings;
import com.vqchien.behaviors.Quack;

public class MallardDuck extends Duck {
  public MallardDuck() {
    super(new FlyWithWings(), new Quack());
  }

  public String display() {
    return "MallardDuck";
  }
}
