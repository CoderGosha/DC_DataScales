using DataBarCode;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using System.Net;
using System.Net.Sockets;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using System.Windows.Media;

namespace DataScalesRepeater
{
    class CWeigth : INotifyPropertyChanged, IDisposable
    {
        public event PropertyChangedEventHandler PropertyChanged;

        //Класс для работы с весами :)
        public string NAME { get; set; }
        public string VES { get; set; }
        public string STABIL { get; set; }
        public string RAW { get; set; }
        public DateTime TIME_VES { get; set; }
        public TYPE_WEIGTH TYPE_CURRENT_WEIGTH { get; set; }
        private List<CWeigthBuffer> LCWeigthBuffer = null;

        private Thread TreadService;
        private bool TreadServiceWork;
        Socket sListener;
        public string DNS_NAME { get; set; }
        public string PORT { get; set; }

        protected void OnPropertyChanged(string name)
        {
            PropertyChangedEventHandler handler = PropertyChanged;
            if (handler != null)
            {
                handler(this, new PropertyChangedEventArgs(name));
            }
        }

        public SolidColorBrush Background
        {
            get
            {
                if (TIME_VES > DateTime.UtcNow.AddMinutes(-1))
                    return new SolidColorBrush(Colors.LightGreen);
                else if (TIME_VES > DateTime.UtcNow.AddHours(-1))
                    return new SolidColorBrush(Colors.LightYellow);

                else if (TIME_VES > DateTime.UtcNow.AddHours(-6))
                    return new SolidColorBrush(Colors.Tomato);
                else
                    return new SolidColorBrush(Colors.LightGray);
            }

            set
            {
                Background = value;
            }
        }

        public string COUNT_BUFFER
        {
            set
            {
                OnPropertyChanged("COUNT_BUFFER");
            }

            get
            {
                if (LCWeigthBuffer != null)
                    return LCWeigthBuffer.Count.ToString();
                else return "NULL";

            }
        }
        public CWeigth(string _Name, TYPE_WEIGTH _TYPE_CURRENT_WEIGTH, string _DNS, string _PORT)
        {
            NAME = _Name;
            TYPE_CURRENT_WEIGTH = _TYPE_CURRENT_WEIGTH;
            LCWeigthBuffer = new List<CWeigthBuffer>();
            LCWeigthBuffer.Add(new CWeigthBuffer("000", "0", "RAW", DateTime.UtcNow));

            PORT = _PORT;
            DNS_NAME = _DNS;

            try
            {
                //Запускаем треды 
                TreadServiceWork = true;
                TreadService = new Thread(TcpServiceCWeigth);
                TreadService.Start();
            }

            catch (Exception ex)
            {
                AddLogExept("CWeigth", "CWeigth", "Thread: " + ex.ToString());
            }

        }

        public void Dispose()
        {
            try
            {
                TreadServiceWork = false;
                TreadService.Abort();

            }

            catch (Exception)
            {

            }

            try
            {
                sListener.Close();
            }

            catch (Exception)
            {

            }
        }



        public void SET_WEIGTH(string _VES, string _STABIL, string _RAW)
        {
            VES = _VES;
            STABIL = _STABIL;
            RAW = _RAW;
            TIME_VES = DateTime.UtcNow;

            while (LCWeigthBuffer.Count > 10000)
            {
                LCWeigthBuffer.RemoveAt(0);
            }

            //Создаем Буффер для отправки...
            LCWeigthBuffer.Add(new CWeigthBuffer(_VES, _STABIL, _RAW, DateTime.UtcNow));

            OnPropertyChanged("VES");
            OnPropertyChanged("STABIL");
            OnPropertyChanged("RAW");
            OnPropertyChanged("TIME_VES");
            OnPropertyChanged("COUNT_BUFFER");
            OnPropertyChanged("Background");

        }

        public void SET_WEIGTH(string _VES, string _STABIL, string _RAW, DateTime _DateTime, string _Fix)
        {
            VES = _VES;
            STABIL = _STABIL;
            RAW = _RAW;
            TIME_VES = _DateTime;

            while (LCWeigthBuffer.Count > 10000)
            {
                LCWeigthBuffer.RemoveAt(0);
            }

            //Создаем Буффер для отправки...
            LCWeigthBuffer.Add(new CWeigthBuffer(_VES, _STABIL, _RAW, TIME_VES, _Fix));

            OnPropertyChanged("VES");
            OnPropertyChanged("STABIL");
            OnPropertyChanged("RAW");
            OnPropertyChanged("TIME_VES");
            OnPropertyChanged("COUNT_BUFFER");
            OnPropertyChanged("Background");

        }

        class CWeigthBuffer
        {
            public string VES { get; set; }
            public string STABIL { get; set; }
            public string RAW { get; set; }
            public string FIX { get; set; }
            public DateTime TIME_VES { get; set; }
            public CWeigthBuffer(string _VES, string _STABIL, string _RAW, DateTime _TIME_VES)
            {
                VES = _VES;
                STABIL = _STABIL;
                RAW = _RAW;
                TIME_VES = _TIME_VES;
                FIX = "0";

            }

            public CWeigthBuffer(string _VES, string _STABIL, string _RAW, DateTime _TIME_VES, string _FIX)
            {
                VES = _VES;
                STABIL = _STABIL;
                RAW = _RAW;
                TIME_VES = _TIME_VES;
                FIX = _FIX;
            }
        }

        private void AddLogInfo(string Module, string Message)
        {
            CLog.WriteInfo(Module, Message);
        }

        private void AddLogExept(string Module, string Func, string Message)
        {
            CLog.WriteException(Module, Func, Message);
        }


        public void UpdateRowBackGround()
        {
            OnPropertyChanged("Background");
        }
        private void TcpServiceCWeigth(object obj)
        {
            ///hfgfgfgfgv
            ///
            try
            {

                // Устанавливаем для сокета локальную конечную точку
                //IPHostEntry ipHost = Dns.GetHostEntry(DNS_NAME);
               // IPAddress ipAddr = ipHost.AddressList[1];
                IPEndPoint ipEndPoint = new IPEndPoint(IPAddress.Any, Int32.Parse(PORT));

                // Создаем сокет Tcp/Ip
                sListener = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);
                // Назначаем сокет локальной конечной точке и слушаем входящие сокеты
                try
                {
                    sListener.Bind(ipEndPoint);
                    sListener.Listen(10);

                    // Начинаем слушать соединения
                    while (TreadServiceWork)
                    {
                        //  Console.WriteLine("Ожидаем соединение через порт {0}", ipEndPoint);
                        AddLogInfo("CWeigth", "Ожидаем соединение через порт " + ipEndPoint);
                        // Программа приостанавливается, ожидая входящее соединение
                        Socket handler = sListener.Accept();
                        //   handler.ReceiveTimeout = 1;
                        //  handler.SendTimeout = 1;
                        //string data = null;

                        //// Мы дождались клиента, пытающегося с нами соединиться

                        //byte[] bytes = new byte[1024];
                        //int bytesRec = handler.Receive(bytes);
                        try
                        {
                            string reply = "Hello";
                            byte[] msg = Encoding.UTF8.GetBytes(reply);
                            handler.Send(msg);
                        }
                        catch (Exception) { }
                        //data += Encoding.UTF8.GetString(bytes, 0, bytesRec);

                        //// Показываем данные на консоли
                        ////Console.Write("Полученный текст: " + data + "\n\n");

                        //AddLogInfo("CWeigth", "Полученный текст: " + data + ":" + data.Length.ToString());

                        //Отправляем клиенту ответ в нужной последловательности байт

                        //// Отправляем ответ клиенту\
                        try
                        {
                            while (TreadServiceWork)
                            {
                                if (LCWeigthBuffer != null)
                                {//
                                    if (LCWeigthBuffer.Count > 0)
                                    {
                                        CWeigthBuffer tmp = LCWeigthBuffer[0];
                                        string reply = "VES=" + tmp.VES + ";;;STABIL=" + tmp.STABIL + ";;;DATETIME=" + tmp.TIME_VES.ToString() + ";;;FIX=" + tmp.FIX + ";;;END";
                                        byte[] msg = Encoding.UTF8.GetBytes(reply);
                                        handler.Send(msg);

                                        LCWeigthBuffer.Remove(tmp);
                                        COUNT_BUFFER = LCWeigthBuffer.Count.ToString();

                                        Thread.Sleep(100);
                                    }
                                }

                                Thread.Sleep(100);

                            }
                        }

                        catch (Exception exe)
                        {
                            AddLogExept("CWeigth", "Session Client", "Похоже клиент отключился" + exe.ToString());
                        }
                        //if (data.IndexOf("<TheEnd>") > -1)
                        //{
                        //    Console.WriteLine("Сервер завершил соединение с клиентом.");
                        //    break;
                        //}

                        handler.Shutdown(SocketShutdown.Both);
                        handler.Close();
                    }
                }
                catch (Exception ex)
                {
                    AddLogExept("CWeigth", "TcpServiceCWeigth", "Выключаем сервер" + ex.ToString());
                }
                finally
                {
                    //Console.ReadLine();
                }

            }

            catch (Exception exee)
            {
                AddLogExept("CWeigth", "TcpServiceCWeigth", "Thread: " + exee.ToString());
            }
        }


    }
}
