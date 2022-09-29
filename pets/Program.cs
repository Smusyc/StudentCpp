using System;
namespace pets
{
    public class Restrictions
    {
        private double left_weight=0, right_weight = 0, ceiling_age=0;
        public Restrictions(double left_br, double right_br, int ceiling_age)
        {
            this.left_weight = left_weight;
            this.right_weight = right_weight;
            this.ceiling_age = ceiling_age;
        }
        public bool IsBetween_weight(double unit)
        {
            if (left_weight <= unit && right_weight >= unit)
                return true;
            else
                return false;
        }
        public bool IsUnder_Ceiling_Age(uint age)
        {
            if (age <= ceiling_age)
                return true;
            else
                return false;
        }
    }
    
    public class Personal_Data
    {
        private string name { get; }
        private uint age;
        private double weight;
        private Restrictions restrict;
        public Personal_Data(string name, uint age, double weight, Restrictions restrict)
        {
                this.name = name;
                if(restrict.IsUnder_Ceiling_Age(age))
                    this.age = age;
                if(restrict.IsBetween_weight(weight))
                    this.weight = weight;
        }
        public Personal_Data(string name, uint age, double weight)
        {
                this.name = name;
                this.age = age;
                this.weight = weight;
        }

        virtual public void Add_Age(uint addition)
        {
            if (restrict.IsUnder_Ceiling_Age(this.age + addition))
            {
                age += addition;
                Console.WriteLine($"Happy Birthday! {name} is {age} now");
            }
            else
                Console.WriteLine($"RIP {name}");
        }
        virtual public void Gain_Weight(double addition)
        {
            if (restrict.IsBetween_weight(weight + addition))
            {
                weight += addition;
                Console.WriteLine($"{name} gained {addition} kilos");
            }
            else
                Console.WriteLine($"{name}, is on a diet. He already has {weight} kilos!");

        }
        public void Loss_Weight(double addition)
        {
            if (restrict.IsBetween_weight(weight - addition))
            {
                weight -= addition;
                Console.WriteLine($"{name} lost {addition} kilos");
            }
            else
                Console.WriteLine($"{name}, I'll feed you. You have only {addition} kilos!");

        }
    }
    abstract public class Animal
    {
        public Personal_Data data;
        protected string food_for_pet="";
        public Animal(string name, uint age, double weight) {
            data = new Personal_Data(name, age, weight);
        }
        abstract public void Voice();
        abstract public void Feed(string food_for_pet);
        
    }

    public class Dog : Animal
    {
        private static Restrictions restrict_dogs;
        public Dog(string name, uint age, double weight):base(name, age, weight)
        {
            food_for_pet = "food_for_dog";
            restrict_dogs = new Restrictions(0.5, 20.0, 18);
            data = new Personal_Data(name, age, weight, restrict_dogs);
        }
        
        override public void Voice()
        {
            Console.WriteLine("Gav-gav");
        }
        override public void Feed(string food_for_animal)
        {
            if(food_for_animal== food_for_pet)
            {
                data.Gain_Weight(1.0);
                Console.WriteLine("Gav)))");
            }
            else
            {
                data.Loss_Weight(1.0);
                Console.WriteLine("o_0");
            }
        }
    }
    public class Cat : Animal
    {
        private static Restrictions restrict_cats;
        public Cat(string name, uint age, double weight) : base(name, age, weight)
        {
            food_for_pet = "food_for_cat";
            restrict_cats = new Restrictions(0.1, 6.0, 15);
            data = new Personal_Data(name, age, weight, restrict_cats);
        }
        override public void Voice()
        {
            Console.WriteLine("Mew");
        }
        override public void Feed(string food_for_animal)
        {
            if (food_for_animal == food_for_pet)
            {
                data.Gain_Weight(0.3);
                Console.WriteLine("Mew)))");
            }
            else
            {
                data.Loss_Weight(0.03);
                Console.WriteLine("o_0");
            }
        }
    }
    public class Hamster : Animal
    {
        private static Restrictions restrict_hamsters;
        public Hamster(string name, uint age, double weight) : base(name, age, weight)
        {
            food_for_pet = "food_for_hamster";
            restrict_hamsters = new Restrictions(0.1, 0.5, 4);
            data = new Personal_Data(name, age, weight, restrict_hamsters);
        }
        override public void Voice()
        {
            Console.WriteLine("Fnufnu");
        }
        override public void Feed(string food_for_animal)
        {
            if (food_for_animal == food_for_pet)
            {
                data.Gain_Weight(0.01);
                Console.WriteLine("FnufnuFnufnuFnufnuFnufnu)))))))");
            }
            else
            {
                data.Loss_Weight(0.01);
                Console.WriteLine("o_0");
            }
        }
    }
    public class Tortle : Animal
    {
        private static Restrictions restrict_tortle;
        public Tortle(string name, uint age, double weight) : base(name, age, weight)
        {
            food_for_pet = "food_for_tortle";
            restrict_tortle = new Restrictions(0.05, 3.0, 100);
            data = new Personal_Data(name, age, weight, restrict_tortle);
        }
        override public void Voice()
        {
            Console.WriteLine("........");
        }
        override public void Feed(string food_for_animal)
        {
            if (food_for_animal == food_for_pet)
            {
                data.Gain_Weight(0.09);
                Console.WriteLine(".......)))))))");
            }
            else
            {
                data.Loss_Weight(0.09);
                Console.WriteLine("_.<(o_0)>._");
            }
        }
    }
    public class Perret : Animal
    {
        private static Restrictions restrict_perret;
        public Perret(string name, uint age, double weight) : base(name, age, weight)
        {
            food_for_pet = "food_for_perret";
            restrict_perret = new Restrictions(0.05, 2.0, 10);
            data = new Personal_Data(name, age, weight, restrict_perret);
        }
        override public void Voice()
        {
            Console.WriteLine("Guhaaa");
        }
        override public void Feed(string food_for_animal)
        {
            if (food_for_animal == food_for_pet)
            {
                data.Gain_Weight(0.1);
                Console.WriteLine("Guhaaa)))))))");
            }
            else
            {
                data.Loss_Weight(0.1);
                Console.WriteLine("O{}o");
            }
        }
    }

    public class Program
    {
        static void Main(string[] args)
        {
            Cat Barsic = new Cat("Barsik", 8,4.5);
            Dog Rex = new Dog("Rex", 4, 6);
            Perret Kesha = new Perret("Kesha", 1, 1.2);
            Barsic.Feed("food_for_dog");
            Rex.Feed("food_for_dog");
            Rex.Feed("food_for_dog");
            Rex.Feed("food_for_dog");
            Rex.Feed("food_for_cat");
            Rex.Voice();
            Kesha.Voice();
            Kesha.data.Add_Age(6);
            Kesha.data.Add_Age(1);
            Kesha.data.Add_Age(1);
        }
    }
}
