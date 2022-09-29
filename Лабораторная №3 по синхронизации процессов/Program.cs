using System;
using System.Collections.Generic;
using System.Threading;

namespace ProducerConsumerFW
{
    internal class Program
    {
        private static int Count = 0;
        static object locker1 = new object();
        static object locker2 = new object();
        static object locker3 = new object();
        public static readonly Queue<int> Buffer = new Queue<int>();
        private static readonly int BufferSize = 10;
        private static readonly Random Rand = new Random();
        private static Thread _producerThread, _consumerThread;
        private static double _producerSpeed = 1, _consumerSpeed = 1;
        private static bool _producerIsPaused = false, _consumerIsPaused = false;
        static bool exit = false;

        private static void Main()
        {
            _producerThread = new Thread(Produce) { Name = $"Producer" };
            _producerThread.Start();
            _consumerThread = new Thread(Consume) { Name = $"Consumer" };
            _consumerThread.Start();
            for (; ; )
            {
                var key = Console.ReadKey(true).Key;
                switch (key)
                {
                    case ConsoleKey.D1:
                        _producerIsPaused = true;
                        _consumerIsPaused = false;
                        break;
                    case ConsoleKey.D2:
                        _producerIsPaused = false;
                        _consumerIsPaused = true;
                        break;
                    case ConsoleKey.Q:
                        if ((int)(_producerSpeed * 10) > 1) _producerSpeed -= 0.1;
                        break;
                    case ConsoleKey.E:
                        if (_producerSpeed < 2.0) _producerSpeed += 0.1;
                        break;
                    case ConsoleKey.A:
                        if ((int)(_consumerSpeed * 10) > 1) _consumerSpeed -= 0.1;
                        break;
                    case ConsoleKey.D:
                        if (_consumerSpeed < 2.0) _consumerSpeed += 0.1;
                        break;
                }
            }
        }

        public static void Produce()
        {
            //MutexObj.WaitOne();
            for (; ; )
            {
                ActionP();
            }
        }

        public static void Consume()
        {
            for (; ; )
            {
                ActionC();
            }
        }

        public static void ActionP()
        {
            lock (locker1) {
                if (Count < 10 && (!_producerIsPaused))
                {
                    Buffer.Enqueue(1);
                    Result();
                    Thread.Sleep((int)(1000 / _producerSpeed));


                    Count++;

                }

            }

        }
        public static void ActionC()
        {
            lock (locker2)
            {
                if (Count > 0 && (!_consumerIsPaused))
                {
                    Buffer.Dequeue();
                    Result();
                    Thread.Sleep((int)(1000 / _consumerSpeed));

                    Count--;

                }

            }


        }
        public static void Result()
        {
            lock (locker3)
            {
                Console.Clear();
                string pState;
                if (_producerIsPaused && !(Count < 10))
                {
                    pState = "Paused";
                }
                else
                    pState = _producerThread.ThreadState.ToString();

                string cState;
                if (_consumerIsPaused && !(Count > 0))
                {
                    cState = "Paused";
                }
                else
                    cState = _consumerThread.ThreadState.ToString();

                Console.WriteLine($"{_producerThread.Name}: Speed [Q, E] - {_producerSpeed:0.0}\tState [1 - Pause] - {pState}");
                Console.WriteLine($"{_consumerThread.Name}: Speed [A, D] - {_consumerSpeed:0.0}\tState [2 - Pause] - {cState}");
                Console.WriteLine($"Buffer filling: {(Count) * 50}%");
            }
        }
    }
}
