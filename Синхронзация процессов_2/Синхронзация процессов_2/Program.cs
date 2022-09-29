using System;
using System.Collections.Generic;
using System.Threading;

namespace ProducerConsumerFW
{
    internal class Program
    {
        static int Count=0;
        static object locker = new object();
        private static readonly Queue<Thread>[] Buffer = new Queue<int>[10];
        private static readonly int BufferSize = 10;
        private static readonly Random Rand = new Random();
        private static Thread _producerThread, _consumerThread;
        private static double _producerSpeed = 1, _consumerSpeed = 1;
        private static bool _producerIsPaused=false, _consumerIsPaused=false;
        static bool exit=false;

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
            for ( ; ; ) { 
                Action('p');
                Result();
            }
        }

        public static void Consume()
        {
            for (; ; )
            {
                Action('c');
                Result();
            }
        }

        public static void Action(char choice)
        {
            lock (locker)
            {
                switch (choice)
                {
                    case 'p':
                        if (Buffer.Length < 10 && (!_producerIsPaused))
                        {
                            Buffer.Enqueue(1);
                            Thread.Sleep((int)(100 / _producerSpeed));
                        }
                        break;
                    case 'c':
                        if (Buffer.Length > 0 && (!_consumerIsPaused))
                        {
                            Buffer.Dequeue();
                            Thread.Sleep((int)(100 / _consumerSpeed));
                        }
                        break;
                }
            }
        }
        public static void Result()
        {
            Console.Clear();
            string pState = _producerIsPaused ? !(Buffer.Length < 10) ? "Paused" : _producerThread.ThreadState.ToString();
            string cState = _consumerIsPaused ? !(Buffer.Length > 0) ? "Paused" : _consumerThread.ThreadState.ToString();

            Console.WriteLine($"{_producerThread.Name}: Speed [Q, E] - {_producerSpeed:0.0}\tState [1 - Pause] - {pState}");
            Console.WriteLine($"{_consumerThread.Name}: Speed [A, D] - {_consumerSpeed:0.0}\tState [2 - Pause] - {cState}");
            Console.WriteLine($"Buffer filling: {(Buffer.Length)*10}%");
        }
    }
}
