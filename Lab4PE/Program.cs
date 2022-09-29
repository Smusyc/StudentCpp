using System;
using System.Collections.Generic;
using System.Text.RegularExpressions;
namespace Lab4PE
{
    class Program
    {
        public static void Recognition(ref string expr_input, ref List<Element> elements_of_expr)
        {
            Regex regex = new Regex(@"\d+\.?\d*|[-\+\*\/\(\)^]|sqrt");
            MatchCollection elements = regex.Matches(expr_input);
            foreach (Match i in elements)
            {
                if (!Microsoft.VisualBasic.Information.IsNumeric(i.Value))
                {
                    switch (i.Value)
                    {
                        case "+":
                            elements_of_expr.Add(new Plus("+"));
                            break;
                        case "-":
                            if (elements_of_expr.Count == 0 || !Microsoft.VisualBasic.Information.IsNumeric(elements_of_expr[elements_of_expr.Count - 1]))
                            {
                                elements_of_expr.Add(new UnMinus("-"));
                                elements_of_expr.Add(new Operands(Convert.ToDouble(-1)));
                            }
                            else
                                elements_of_expr.Add(new Minus("-"));
                            break;
                        case "^":
                            elements_of_expr.Add(new Pow("^"));
                            break;
                        case "(":
                            elements_of_expr.Add(new Left_br("("));
                            break;
                        case ")":
                            elements_of_expr.Add(new Right_br(")"));
                            break;
                        case "/":
                            elements_of_expr.Add(new Dir("/"));
                            break;
                        case "*":
                            elements_of_expr.Add(new Mul("*"));
                            break;
                    }
                    if (i.Value == "sqrt")
                        elements_of_expr.Add(new Sqr("sqrt"));
                }else
                    elements_of_expr.Add(new Operands(Convert.ToDouble(i.Value)));
            }
        }

        public static void ToRPN(ref List<Element> elements)
        {
            List<Element> outputSeparated = new List<Element>();
            Stack<Element> stack = new Stack<Element>();


            foreach (Element c in elements)
            {
                if (Microsoft.VisualBasic.Information.IsNumeric(c.GetWritten()) || ((Operation)c)._fix == "postfix")
                {
                    outputSeparated.Add(c);

                }
                else if (((Operation)c)._fix == "prefix")
                {
                    stack.Push(c);
                }
                else if (((Operation)c).GetWritten() == "(")
                {
                    stack.Push(c);
                }
                else if (((Operation)c).GetWritten() == ")")
                {
                    while (stack.Count > 0 && ((Operation)(stack.Peek())).GetWritten() != "(")
                        outputSeparated.Add(stack.Pop());
                    if(stack.Count > 0)
                        stack.Pop();
                }
                else if (((Operation)c)._nary == "binary")
                {
                    while (stack.Count > 0 && (((Operation)(stack.Peek()))._fix == "prefix" | ((Operation)(stack.Peek())).GetPriority() >= ((Operation)c).GetPriority()))
                    {
                        if ((((Operation)(stack.Peek())).GetWritten()) == "(")
                        {
                            stack.Pop();
                            break;
                        }
                        outputSeparated.Add(stack.Pop());
                    }
                    stack.Push(c);
                }
            }
            if (stack.Count > 0)
                foreach (Element c in stack)
                    outputSeparated.Add(c);

            elements =outputSeparated;
        }


        public static double Calculate(string expr_input)
        {
            Stack<Operation> operators = new Stack<Operation>();
            Stack<Operands> operands = new Stack<Operands>();
            List<Element> elements = new List<Element>();
            Recognition(ref expr_input, ref elements);
            ToRPN(ref elements);
            elements.Reverse();
            foreach (Element element in elements)
            {
                if(Microsoft.VisualBasic.Information.IsNumeric(element.GetWritten()))
                    operands.Push((Operands)element);
                else
                    operators.Push((Operation)element);
            }
            Stack<Operation> rev = new Stack<Operation>();
            while (operators.Count!=0)
            {
                rev.Push(operators.Pop());
            }

            foreach (Operation i in rev)
            {
                i.Calc(ref operands);
            }
            return Convert.ToDouble((operands.Pop()).value);
        }
        abstract public class Element
        {
            protected string writen;
            public Element(string writen)
            {
                this.writen = writen;
            }
            public Element() { }
            public string GetWritten()
            {
                return writen;
            }
        }


        public class Operands : Element
        {
            public double value { get; }
            public Operands(string writen) : base(writen)
            {
                this.value = Convert.ToDouble(writen);
            }
            public Operands(double value) : base()
            {
                this.writen = Convert.ToString(value);
                this.value = value;
            }
        }


        public class Operation: Element
        {
            protected int priority;
            public string _fix;
            public string _nary;

            public Operation(string writen):base(writen)
            {
            }
            public virtual void Calc(ref Stack<Operands> operands)
            { }
            public int GetPriority()
            {
                return priority;
            }
        }

        public class Plus : Operation
        {
            public Plus(string writen) : base(writen)
            {
                _fix = "infix";
                _nary = "binary";
                this.priority = 1;
            }
            public override void Calc(ref Stack<Operands> operands)
            {
                operands.Push(new Operands((operands.Pop()).value+(operands.Pop()).value));
            }
        }
        public class Minus : Operation
        {
            public Minus(string writen) : base(writen)
            {
                _fix = "infix";
                _nary = "binary";
                this.priority = 1;
            }
            public override void Calc(ref Stack<Operands> operands)
            {
                operands.Push(new Operands((operands.Pop()).value - (operands.Pop()).value));
            }
        }

        public class Mul : Operation
        {
            public Mul(string writen) : base(writen)
            {
                _fix = "infix";
                _nary = "binary";
                this.priority = 2;
            }
            public override void Calc(ref Stack<Operands> operands)
            {
                operands.Push(new Operands((operands.Pop()).value * (operands.Pop()).value));
            }
        }
        public class Dir : Operation
        {
            public Dir(string writen) : base(writen)
            {
                _fix = "infix";
                _nary = "binary";
                this.priority = 2;
            }
            public override void Calc(ref Stack<Operands> operands)
            {
                operands.Push(new Operands((operands.Pop()).value / (operands.Pop()).value));
            }
        }

        public class Sqr : Operation
        {
            public Sqr(string writen) : base(writen)
            {
                _fix = "prefix";
                _nary = "unary";
                this.priority = 3;
            }
            public override void Calc(ref Stack<Operands> operands)
            {
                operands.Push(new Operands(Math.Pow((operands.Pop()).value, 1.0/2)));
            }
        }

        public class Pow : Operation
        {
            public Pow(string writen) : base(writen)
            {
                _fix = "infix";
                _nary = "binary";
                this.priority = 3;
            }
            public override void Calc(ref Stack<Operands> operands)
            {
                operands.Push(new Operands(Math.Pow((operands.Pop()).value, (operands.Pop()).value)));
            }
        }

        public class UnMinus : Operation
        {
            public UnMinus(string writen) : base(writen)
            {
                _fix = "prefix";
                _nary = "unary";
                this.priority = 4;
            }
            public override void Calc(ref Stack<Operands> operands)
            {
                operands.Push(new Operands((operands.Pop()).value*(operands.Pop()).value));
            }
        }
        public class Left_br : Operation
        {
            public Left_br(string writen) : base(writen)
            {
                _fix = "none";
                _nary = "none";
                this.priority = 5;
            }
            public override void Calc(ref Stack<Operands> operands)
            {
                operands.Push(new Operands((operands.Pop()).value * (operands.Pop()).value));
            }
        }
        public class Right_br : Operation
        {
            public Right_br(string writen) : base(writen)
            {
                _fix = "none";
                _nary = "none";
                this.priority =5;
            }
            public override void Calc(ref Stack<Operands> operands)
            {
                operands.Push(new Operands((operands.Pop()).value * (operands.Pop()).value));
            }
        }

        static void Main(string[] args)
        {

            string expr=Console.ReadLine();
            Console.WriteLine(Calculate(expr));

        }
    }
}
