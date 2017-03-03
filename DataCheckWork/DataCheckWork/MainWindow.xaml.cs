using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.ComponentModel;
using System.Diagnostics;
using System.IO;
using System.Linq;
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

namespace DataCheckWork
{
    /// <summary>
    /// Логика взаимодействия для MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {

        public static LogItemList LogList = new LogItemList();
        private ObservableCollection<DiagnosticUnit> _tableUnit;

        private Thread TreadService;
        private bool TreadServiceWork;

        public MainWindow()
        {
            InitializeComponent();

            ListBoxLog.DataContext = LogList;
            _tableUnit = new ObservableCollection<DiagnosticUnit>();


            DiagnosticUnit tmp = new DiagnosticUnit();
            tmp.NUM_PP = "1";
            tmp.Name = "DataScales";
            tmp.NameProc = "Scales";
            tmp.FileStart = "Scales.exe";
            tmp.FileCheck = "DataScales-KeepAlive.lock";


            _tableUnit.Add(tmp);

            GridDiag.DataContext = _tableUnit;

            //Запускаем треды 
            TreadServiceWork = true;
            TreadService = new Thread(DiagnosticFunc);
            TreadService.Start();
            SaveLog("System", "Запуск приложения", 0);



            InitializeComponent();


        }

      
        ~MainWindow()
        {

        }


        public class DiagnosticUnit : INotifyPropertyChanged
        {
            public event PropertyChangedEventHandler PropertyChanged;

            public string NUM_PP { get; set; }
            public string Name { get; set; }
            public string NameProc { get; set; }
            public string FileStart { get; set; }
            public string FileCheck { get; set; }
            public int timecheck = 10;
            public int processSuspend = 0;
            public int CountProcess = 0;
            public string TIMECHECK
            {
                get
                {
                    return timecheck.ToString();
                }
                set
                {
                    timecheck = Int32.Parse(value);
                }
            }

            public string PROCESSCOUNT
            {
                get
                {
                    return CountProcess.ToString() + "/" + processSuspend.ToString();
                }
                set
                {
                    CountProcess = Int32.Parse(value);
                    OnPropertyChanged("PROCESSCOUNT");
                   // OnPropertyChanged("processSuspend");
                }
            }

            public SolidColorBrush Background
            {
                get
                {

                    if (CHECKACTIVE == 1)
                        return new SolidColorBrush(Colors.WhiteSmoke);

                    else if (CHECKACTIVE == -1)
                        return new SolidColorBrush(Colors.Tomato);

                    else 
                        return new SolidColorBrush(Colors.Yellow);


                }

                set
                {
                    Background = value;
                }
            }

            public int CHECKACTIVE
            {
                get
                {
                    return CheckActive;
                }

                set
                {

                    CheckActive = value;
                    OnPropertyChanged("CheckActive");
                    OnPropertyChanged("Background");
                }

            }

            public int CheckActive = 0;

            public string LASTCHECK
            {
                get
                {

                    return LastCheck;
                }
                set
                {
                    LastCheck = value;
                    OnPropertyChanged("LastCheck");

                }
            }
            public string RESTART
            {
                get
                {

                    return Restart.ToString();
                }
                set
                {
                    Restart = Int32.Parse(value);
                    OnPropertyChanged("Restart");
                }
            }
            public string LASTRESTART
            {
                get
                {

                    return LastRestart;
                }
                set
                {
                    LastRestart = value;
                    OnPropertyChanged("LastRestart");
                }
            }

            public int Restart = 0;


            public string LastCheck;
            public string LastRestart;
            public string DateFile;

            protected void OnPropertyChanged(string name)
            {
                PropertyChangedEventHandler handler = PropertyChanged;
                if (handler != null)
                {
                    handler(this, new PropertyChangedEventArgs(name));
                }
            }

            public void Diagnostics()
            {



                PROCESSCOUNT = KillProcSuspended().ToString();
                LASTCHECK = DateTime.Now.ToString();

                try
                {
                    if (!(File.Exists(FileCheck)))
                    { /*все пропало, файла нет, надо срочно что-то делать*/
                        CHECKACTIVE = -1;
                        return;
                    }

                    //Последнее изменение файла
                    DateTime DF = File.GetLastWriteTime(FileCheck);

                    if (DF < DateTime.Now.AddSeconds(-timecheck))
                    {
                        CHECKACTIVE = 0;
                        Restarting();
                    }

                    CHECKACTIVE = 1;
                }

                catch (Exception ee)
                {
                   // SaveLog("System", "Restart: " + ee.Message, -1);
                    CHECKACTIVE = -1;
                }

            }

            public void Restarting()
            {
                try
                {
                    KillProc();
                    //Запускаем exe файл
                    Thread.Sleep(200);

                    //создаем новый процесс
                    Process proc = new Process();
                    //Запускаем Блокнто
                    proc.StartInfo.FileName = FileStart;
                    proc.StartInfo.Arguments = "";
                    proc.Start();

                    int R = Restart + 1;
                    RESTART = R.ToString();
                    LASTRESTART = DateTime.Now.ToString();

                    Thread.Sleep(5000);
                }

                catch (Exception ee)
                {
                   // SaveLog("System", "Restart: " + ee.Message, -1);
                    //MessageBox.Show(ee.ToString());
                    CHECKACTIVE = -1;
                    Thread.Sleep(5000);
                }
            }


            public void KillProc()
            {
                    foreach (var process in Process.GetProcessesByName(NameProc))
                    {
                      //  MessageBox.Show(process.StartTime.ToString() + process.ProcessName.ToString());
                       if (!process.HasExited)//Если не отвечает
                       {
                            process.CloseMainWindow();
                            Thread.Sleep(200);
                            process.Kill();
                        }
                        //process.Close();
                    }
            }

            public int KillProcSuspended()
            {
                CountProcess = 0;
                processSuspend = 0;
                foreach (var process in Process.GetProcessesByName(NameProc))
                {
                    //f (process.
                    //  MessageBox.Show(process.StartTime.ToString() + process.ProcessName.ToString());
                    //process.CloseMainWindow();
                    CountProcess++;
                    if (process.HasExited)//Если не отвечает
                    {
                        processSuspend++;
                        try
                        {
                            process.Kill();
                        }
                        catch
                        {

                        }
                    }
                }
                return CountProcess;
            }
        }

        private void DiagnosticFunc()
        {

            while (TreadServiceWork)
            {
                try
                {
                    Dispatcher.Invoke(new Action(() =>
                    {
                        DateUpdate.Text = DateTime.Now.ToString();
                    }));
                }
                catch (Exception)
                {

                }

                //Запускаем проверку

                foreach (DiagnosticUnit elem in _tableUnit)
                {

                    elem.Diagnostics();
                }

                // SaveLogThread("System", "Check", 0);
                Thread.Sleep(200);

            }
        }

        private void Window_Closed_1(object sender, EventArgs e)
        {
            TreadServiceWork = false;
            TreadService.Abort();
        }

        public static void SaveLog(string _Component, string _Events, int _Status)
        {
            //добавляем в список
            LogList.Add(new LogItem(DateTime.Now, _Component, _Events, _Status));

        }

        public void SaveLogThread(string _Component, string _Events, int _Status)
        {

            try
            {
                Dispatcher.Invoke(new Action(() =>
                {
                    //добавляем в список
                    LogList.Add(new LogItem(DateTime.Now, _Component, _Events, _Status));
                }));

            }

            catch (Exception)
            {
                //Случился какой то (((
            }



        }

        public class LogItem
        {
            public LogItem(DateTime _DateEvents, string _Component, string _Events, int _Status)
            {
                DateEvents = _DateEvents;
                Component = _Component;
                Events = _Events;
                Status = _Status;

                if (Status == 1)
                { //Good
                    //true
                    StatusImage = "icon/box_green.png";
                }

                else if (Status == -1) //Error
                { //Good
                    //true
                    StatusImage = "icon/box_red.png";
                }

                else if (Status == 2) //warning
                { //Good
                    //true
                    StatusImage = "icon/box_yellow.png";
                }

                else if (Status == 0) //debug
                { //Good
                    //true
                    StatusImage = "icon/box_grey.png";
                }


            }
            public DateTime DateEvents { get; set; }
            public string Component { get; set; }
            public string Events { get; set; }
            public int Status { get; set; }
            public string StatusImage { get; set; }


        }

        public class LogItemList : ObservableCollection<LogItem>
        {
            private int CountLabelBox = 250;
            protected override void InsertItem(int index, LogItem item)
            {
                // Dispatcher.Invoke(DispatcherPriority.Normal, delegate() { base.InsertItem(0, item); });
                //  Dispatcher.BeginInvoke();

                //_dispatcher.Dispatcher.Invoke(new Action(() =>
                //{

                //    //Тут делаем, то что нужно


                //}));

                base.InsertItem(0, item);

                while (base.Count > CountLabelBox)
                {
                    base.RemoveAt(base.Count - 1);
                }

                //Сохраняем в лог
                string log = item.DateEvents.ToString() + ";;;" + item.Status.ToString() + ";;;" + item.Component + ";;;" + item.Events;
                //FileLogs.SaveLogToFile(log);


            }
        }



    }
}
