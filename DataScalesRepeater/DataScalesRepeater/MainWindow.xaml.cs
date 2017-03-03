using DataBarCode;
using System;
using System.Collections.Generic;
using System.Configuration;
using System.Linq;
using System.Net;
using System.Net.Sockets;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;

namespace DataScalesRepeater
{
    enum TYPE_WEIGTH { AMT_LPC_PU8 }

    /// <summary>
    /// Логика взаимодействия для MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {

        private Thread TreadService;
        private bool TreadServiceWork;
        Socket sListener;
        TcpListener Listener; // Объект, принимающий TCP-клиентов
        string DNS_NAME;
        string PORT;
        List<CWeigth> LCWeigth = null;
        static CWeigth LPC_PU8 = null;
        static CWeigth LPC_PU6 = null;
        static TYPE_WEIGTH TYPE_CURENT_WIGTH;

        private Thread TreadServiceListener;
        private bool TreadServiceListenerWork;


        private Thread TreadUi;
        private bool TreadSUiWork;
        public static int CountClient = 0;

        public static bool debug = false;
        public MainWindow()
        {
            InitializeComponent();
            CLog.DayToSave = 100;
            CLog.InitCLog();

            AddLogInfo("DataScalesRepeater", "Start Programm");

            LCWeigth = new List<CWeigth>();

            if (ConfigurationManager.AppSettings["TYPE_WEIGTH"] == "AMT_LPC_PU8")
            {
                TYPE_CURENT_WIGTH = TYPE_WEIGTH.AMT_LPC_PU8;
                LPC_PU8 = new CWeigth("АМТ. ЛПЦ-1. ПУ-8", TYPE_CURENT_WIGTH, ConfigurationManager.AppSettings["DNS_SERVER"], ConfigurationManager.AppSettings["WEIGTH_PORT_1"]);
                LPC_PU6 = new CWeigth("АМТ. ЛПЦ-1. ПУ-6", TYPE_CURENT_WIGTH, ConfigurationManager.AppSettings["DNS_SERVER"], ConfigurationManager.AppSettings["WEIGTH_PORT_2"]);
                LCWeigth.Add(LPC_PU8);
                LCWeigth.Add(LPC_PU6);
            }

            if (ConfigurationManager.AppSettings["DEBUG"] == "1")
                debug = true;

            DataGridScales.DataContext = LCWeigth;

            TreadSUiWork = true;
            TreadUi = new Thread(TreadUiUpdater);
            TreadUi.Start();

            //Автостарт

            if (ConfigurationManager.AppSettings["AUTOSTART"] == "1")
            {
                //Запускаем сервер
                AddLogInfo("DataScalesRepeater", "Starting Server");
                AddLogInfo("DataScalesRepeater", "Reading Config");
                DNS_NAME = ConfigurationManager.AppSettings["DNS_SERVER"];
                PORT = ConfigurationManager.AppSettings["PORT_SERVER"];


                ////Запускаем треды 
                //TreadServiceWork = true;
                //TreadService = new Thread(TcpService);
                //TreadService.Start();


                TreadServiceListenerWork = true;
                TreadServiceListener = new Thread(TcpServiceListener);
                TreadServiceListener.Start();

            }
        }

        private void TreadUiUpdater(object obj)
        {
            while (TreadSUiWork)
            {
                try
                {
                    foreach (var el in LCWeigth)
                    {
                        el.UpdateRowBackGround();
                    }

                    Dispatcher.Invoke(new Action(() =>
                    {
                        ClientCountLbl.Text = "Count Client: " + CountClient.ToString();

                    }));

                }

                catch (Exception ex)
                {

                }

                finally
                {
                    Thread.Sleep(1000);
                }
            }
        }

        private void AddLogInfo(string Module, string Message)
        {
            CLog.WriteInfo(Module, Message);

            string OutStr;
            OutStr = DateTime.UtcNow.ToString();
            OutStr += ":";
            OutStr += Message;

            Dispatcher.Invoke(new Action(() =>
            {
                LogList.Items.Add(OutStr);

                while (LogList.Items.Count > 50)
                {
                    //Удаляем лишнее
                    LogList.Items.RemoveAt(0);
                }
            }));

        }

        private void AddLogExept(string Module, string Func, string Message)
        {
            CLog.WriteException(Module, Func, Message);

            string OutStr;
            OutStr = DateTime.UtcNow.ToString();
            OutStr += ":";
            OutStr += Message;

            Dispatcher.Invoke(new Action(() =>
            {
                LogList.Items.Add(OutStr);

            }));

        }

        private static void AddLogStatic(string Module, string Func, string Message)
        {
            CLog.WriteException(Module, Func, Message);
        }



        private void StartBtn_Click_1(object sender, RoutedEventArgs e)
        {
            //Запускаем сервер
            AddLogInfo("DataScalesRepeater", "Starting Server");
            AddLogInfo("DataScalesRepeater", "Reading Config");
            DNS_NAME = ConfigurationManager.AppSettings["DNS_SERVER"];
            PORT = ConfigurationManager.AppSettings["PORT_SERVER"];


            ////Запускаем треды 
            //TreadServiceWork = true;
            //TreadService = new Thread(TcpService);
            //TreadService.Start();


            TreadServiceListenerWork = true;
            TreadServiceListener = new Thread(TcpServiceListener);
            TreadServiceListener.Start();
        }

        private void TcpService(object obj)
        {
            ///hfgfgfgfgv
            ///
            try
            {

                // Устанавливаем для сокета локальную конечную точку
                IPHostEntry ipHost = Dns.GetHostEntry(DNS_NAME);
                IPAddress ipAddr = ipHost.AddressList[1];
                IPEndPoint ipEndPoint = new IPEndPoint(IPAddress.Any, Int32.Parse(PORT));

                // Создаем сокет Tcp/Ip
                sListener = new Socket(ipAddr.AddressFamily, SocketType.Stream, ProtocolType.Tcp);
                // Назначаем сокет локальной конечной точке и слушаем входящие сокеты
                try
                {
                    sListener.Bind(ipEndPoint);
                    sListener.Listen(10);

                    // Начинаем слушать соединения
                    while (TreadServiceWork)
                    {
                        //  Console.WriteLine("Ожидаем соединение через порт {0}", ipEndPoint);
                        AddLogInfo("TcpService", "Ожидаем соединение через порт " + ipEndPoint);
                        // Программа приостанавливается, ожидая входящее соединение
                        Socket handler = sListener.Accept();
                        //   handler.ReceiveTimeout = 1;
                        //  handler.SendTimeout = 1;

                        try
                        {
                            string reply = "Hello";
                            byte[] msg = Encoding.UTF8.GetBytes(reply);
                            handler.Send(msg);
                        }
                        catch (Exception) { }

                        //Клиент подключился ... Теперь бесконечно долго читаем инфу...
                        try
                        {
                            while (TreadServiceWork)
                            {
                                string data = null;

                                // Мы дождались клиента, пытающегося с нами соединиться
                                byte[] bytes = new byte[1024];
                                int bytesRec = handler.Receive(bytes);
                                data += Encoding.UTF8.GetString(bytes, 0, bytesRec);
                                AddLogInfo("TcpService", "Полученный текст: " + data + ":" + data.Length.ToString());
                                ParsingRawWeigth(data);


                                try
                                {
                                    string reply = "ok";
                                    byte[] msg = Encoding.UTF8.GetBytes(reply);
                                    handler.Send(msg);
                                }
                                catch (Exception) { }
                            }
                        }

                        catch (Exception exe)
                        {
                            AddLogExept("DataScalesRepeater", "Session Client", "Похоже клиент отключился" + exe.ToString());
                        }

                        handler.Shutdown(SocketShutdown.Both);
                        handler.Close();
                    }
                }
                catch (Exception ex)
                {
                    AddLogExept("TcpService", "TcpService", "StopBtn_Click_1: " + ex.ToString());
                }
                finally
                {
                    //Console.ReadLine();
                }

            }

            catch (Exception exee)
            {
                AddLogExept("TcpService", "TreadServiceWork", "Thread: " + exee.ToString());
            }
        }

        private void TcpServiceListener()
        {
            int Port = int.Parse(ConfigurationManager.AppSettings["PORT_SERVER"]);
            // Создаем "слушателя" для указанного порта
            Listener = new TcpListener(IPAddress.Any, Port);
            Listener.Start(); // Запускаем его

            AddLogInfo("TcpService", "Ожидаем соединение через порт " + Port.ToString());
            // В бесконечном цикле
            while (TreadServiceListenerWork)
            {
                // Принимаем нового клиента
                TcpClient Client = Listener.AcceptTcpClient();
                // Создаем поток
                AddLogInfo("TcpService", " + 1 Client: " + Client.Client.RemoteEndPoint.ToString());
                Thread Thread = new Thread(new ParameterizedThreadStart(ClientThread));
                // И запускаем этот поток, передавая ему принятого клиента
                Thread.Start(Client);
            }

        }

        static void ClientThread(Object StateInfo)
        {
            new Client((TcpClient)StateInfo);
        }

        class Client
        {

            // Конструктор класса. Ему нужно передавать принятого клиента от TcpListener
            public Client(TcpClient Client)
            {
                CountClient++;
                // Код простой HTML-странички
                string Str = "Hello. DataScales by DataCenter Automatic";
                // Приведем строку к виду массива байт
                byte[] Buffer = Encoding.ASCII.GetBytes(Str);
                // Отправим его клиенту
                Client.GetStream().Write(Buffer, 0, Buffer.Length);

                try
                {
                    while (true)
                    {

                        string Request = "";
                        // Буфер для хранения принятых от клиента данных
                        byte[] BufferIN = new byte[1024];
                        // Переменная для хранения количества байт, принятых от клиента
                        int Count;
                        // Читаем из потока клиента до тех пор, пока от него поступают данные
                        try
                        {
                            if ((Count = Client.GetStream().Read(BufferIN, 0, BufferIN.Length)) > 0)
                            {
                                // Преобразуем эти данные в строку и добавим ее к переменной Request
                                Request = Encoding.ASCII.GetString(BufferIN, 0, Count);
                                AddLogStatic("DataRepeater", "Client SEND: " + Client.Client.RemoteEndPoint.ToString(), Request);
                                //AddLogInfo("TcpService", "Полученный текст: " + Request + ":" + Request.Length.ToString());
                                ParsingRawWeigth(Request);
                            }

                        }

                        catch (Exception exe)
                        {

                            AddLogStatic("DataRepeater", "Client: " + Client.Client.RemoteEndPoint.ToString(), exe.ToString());
                        }
                        Str = "Ok";
                        // Приведем строку к виду массива байт
                        Buffer = Encoding.ASCII.GetBytes(Str);
                        // Отправим его клиенту
                        Client.GetStream().Write(Buffer, 0, Buffer.Length);
                    }

                }

                catch (Exception) { }
                CountClient--;
                // Закроем соединение
                Client.Close();
            }
        }

        private void StopBtn_Click_1(object sender, RoutedEventArgs e)
        {//Останавливаем сервер
            try
            {
                AddLogInfo("DataScalesRepeater", "Stoping Server");

                sListener.Close();
                TreadServiceWork = false;
                Thread.Sleep(500);
                TreadService.Abort();
            }

            catch (Exception ex)
            {
                AddLogInfo("DataScalesRepeater", "StopBtn_Click_1: " + ex.Message);
            }

        }

        private void Window_Closed_1(object sender, EventArgs e)
        {
            //try
            //{
            //    AddLogInfo("DataScalesRepeater", "Stop Programm");

            //    sListener.Close();
            //    TreadServiceWork = false;
            //    TreadService.Abort();
            //}

            //catch (Exception ex)
            //{
            //}


            try
            {
                AddLogInfo("DataScalesRepeater", "Stop Programm");
                TreadServiceListenerWork = false;

                // Если "слушатель" был создан
                if (Listener != null)
                {
                    // Остановим его
                    Listener.Stop();
                }

                TreadServiceListener.Abort();
            }

            catch (Exception ex)
            {
            }

            try
            {
                AddLogInfo("DataScalesRepeater", "Stop Programm");
                sListener.Close();
                TreadSUiWork = false;
                TreadUi.Abort();
                TreadSUiWork = true;
            }

            catch (Exception ex)
            {
            }



            try
            {
                if (LPC_PU8 != null)
                {
                    LPC_PU8.Dispose();
                }

                if (LPC_PU6 != null)
                {
                    LPC_PU6.Dispose();
                }
            }

            catch (Exception ex)
            {
            }
        }

        private static void ParsingRawWeigth(string RAW)
        {
            if (debug)
            {//Пишем все в файл

                AddLogStatic("DataRepeater", "ParsingRawWeigth_DEBUG", RAW);

            }

            try
            {
                switch (TYPE_CURENT_WIGTH)
                {
                    case TYPE_WEIGTH.AMT_LPC_PU8:
                        {//Это арм ПУ-8 костыль на котсыле так и будем писать значит
                            ParsingRawWeigthPu8(RAW);
                            break;
                        }

                }

            }

            catch (Exception ex)
            {
                AddLogStatic("DataRepeater", "ParsingRawWeigth", ex.ToString());
            }

        }

        private static void ParsingRawWeigthPu8(string RAW)
        {

            ///////////Сама обработка
            //Сейчас просто впиливаем данные туда
            try
            {
                //Старый алгоритм
                try
                {
                    Double W = Double.Parse(RAW);
                    LPC_PU8.SET_WEIGTH(W.ToString(), "1", RAW);
                }
                catch
                {


                    //Новый алгоритм
                    //
                    int nStart = RAW.IndexOf("N=");
                    if (nStart == -1)
                        throw new System.IndexOutOfRangeException("Not index N");

                    string NSend = RAW.Substring(nStart + 2, 1);
                    if (NSend == "0")
                    {
                        //Посылка для обычного веса
                        //Определеим вес
                        int vesStart = RAW.IndexOf("VES=");
                        int vesEnd = RAW.IndexOf(";END");
                        string Ves = RAW.Substring(vesStart + 4, vesEnd - (vesStart + 4));
                        //Теперь найдем номер весов

                        int nomStart = RAW.IndexOf("NOM=");
                        int nomEnd = RAW.IndexOf(";VES=");
                        string Nom = RAW.Substring(nomStart + 4, nomEnd - (nomStart + 4));
                        if (Nom == "8")
                        {//Посыка для 6 весов
                            LPC_PU8.SET_WEIGTH(Ves, "1", RAW);
                        }
                        else if (Nom == "6")
                        {//Посыка для 6 весов
                            LPC_PU6.SET_WEIGTH(Ves, "1", RAW);
                        }

                        else
                        {
                            AddLogStatic("DataRepeater", "ParsingRawWeigthPu8", "Неопределен номер весов: " + Nom);

                        }
                    }

                    else if (NSend == "1")
                    {//Для посылок с фиксированным весом

                        //Определеим вес
                        int vesStart = RAW.IndexOf("VES=");
                        int vesEnd = RAW.IndexOf(";DATETIME");
                        string Ves = RAW.Substring(vesStart + 4, vesEnd - (vesStart + 4));
                        //Теперь найдем номер весов

                        int nomStart = RAW.IndexOf("NOM=");
                        int nomEnd = RAW.IndexOf(";VES=");
                        string Nom = RAW.Substring(nomStart + 4, nomEnd - (nomStart + 4));
                        //Определим время
                        int timeStart = RAW.IndexOf("DATETIME=");
                        int timeEnd = RAW.IndexOf(";FIX=");
                        string timeS = RAW.Substring(timeStart + 9, timeEnd - (timeStart + 9));

                        //Определим бит фиксации
                        int fixStart = RAW.IndexOf("FIX=");
                        int fixEnd = RAW.IndexOf(";END");
                        string fixS = RAW.Substring(fixStart + 4, fixEnd - (fixStart + 4));

                        if (Nom == "8")
                        {//Посыка для 8 весов
                            LPC_PU8.SET_WEIGTH(Ves, "1", RAW, DateTime.Parse(timeS), fixS);
                        }


                        else if (Nom == "6")
                        {//Посыка для 8 весов
                            LPC_PU6.SET_WEIGTH(Ves, "1", RAW, DateTime.Parse(timeS), fixS);
                        }

                        else
                        {
                            AddLogStatic("DataRepeater", "ParsingRawWeigthPu8", "Неопределен номер весов: " + Nom);

                        }
                    }
                    else
                    {
                        AddLogStatic("DataRepeater", "ParsingRawWeigthPu8", "Else");
                    }
                }

            }

            catch (Exception exe)
            {
                AddLogStatic("DataRepeater", "ParsingRawWeigthPu8", exe.ToString());
            }
        }

        private void StartBtn_Copy_Click_1(object sender, RoutedEventArgs e)
        {
            //  LPC_PU8.SET_WEIGTH("1", "0", "TEST");
            ParsingRawWeigth("N=0;NOM=8;VES=2;END");
            ParsingRawWeigth("N=0;NOM=6;VES=3;END");

            ParsingRawWeigth("N=1;NOM=8;VES=5;DATETIME=15.12.2016 18:00:04;FIX=1;END");
            ParsingRawWeigth("N=1;NOM=6;VES=6;DATETIME=15.12.2016 18:00:04;FIX=1;END");
        }
    }
}
