package com.vqchien;

import com.vqchien.interfaces.FlyBehavior;
import com.vqchien.interfaces.QuackBehavior;

@lombok.Data
@lombok.AllArgsConstructor
public abstract class Duck {
  private FlyBehavior flyBehavior;
  private QuackBehavior quackBehavior;

  public abstract String display();

  public String performFly() {
    return flyBehavior.fly();
  }

  public String performQuack() {
    return quackBehavior.quack();
  }
}
