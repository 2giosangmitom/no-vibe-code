package com.vqchien;

import com.vqchien.behaviors.FlyNoWay;
import com.vqchien.behaviors.Squeak;

public class RubberDuck extends Duck {
    public RubberDuck() {
        super(new FlyNoWay(), new Squeak());
    }

    public String display() {
        return "RubberDuck";
    }
}
