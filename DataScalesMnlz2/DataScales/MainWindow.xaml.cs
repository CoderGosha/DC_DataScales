using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.ComponentModel;
using System.Data;
using System.Data.SqlClient;
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
using System.Data.OracleClient;
using System.Text.RegularExpressions;
using System.IO;


namespace DataScales
{
    /// <summary>
    /// Логика взаимодействия для MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        public static LogItemList LogList = new LogItemList();
        private ObservableCollection<ScalesUnit> _tableUnit;
        private Thread TreadService;
        private bool TreadServiceWork;

        private Thread TreadOracle;
        private bool TreadOracleWork;
        private bool CheckWorkedBool;

        private Thread CheckWorkedThread;

        private static ObservableCollection<RecordByOracle> _BuffByOracle;

        public MainWindow()
        {
            InitializeComponent();

            Title += " StartTime: " + DateTime.Now.ToString();

            ListBoxLog.DataContext = LogList;
            SaveLog("System", "Запуск приложения", 0);

            _tableUnit = new ObservableCollection<ScalesUnit>();


            ScalesUnit tmp = new ScalesUnit();
            tmp.NUM_PP = "3";
            tmp.Name = "МНЛЗ-2. Ручей 3";
            tmp.IP_BD = "10.50.50.3";
            // tmp.WIGTH = "0";
            _tableUnit.Add(tmp);

            tmp = new ScalesUnit();
            tmp.NUM_PP = "4";
            tmp.Name = "МНЛЗ-2. Ручей 4";
            tmp.IP_BD = "10.50.50.4";
            _tableUnit.Add(tmp);

            GridScales.DataContext = _tableUnit;

            _BuffByOracle = new ObservableCollection<RecordByOracle>();


            CheckWorkedBool = true;
            CheckWorkedThread = new Thread(CheckWorked);
            CheckWorkedThread.Start();

            //Запускаем треды 
            TreadServiceWork = true;
            TreadService = new Thread(GetsWeigth);
            TreadService.Start();

            //Запускаем треды 
            TreadOracleWork = true;
            TreadOracle = new Thread(SendOracle);
            TreadOracle.Start();



        }

        private void Button_Test_Click(object sender, RoutedEventArgs e)
        {
            //Тестим 

            foreach (ScalesUnit scales in _tableUnit)
            {
                scales.ConnectBd();
                scales.GetWigth();
                scales.CloseConn();
            }


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
                //if (Dispatcher.Thread != System.Threading.Thread.CurrentThread)
                //{
                //    Dispatcher.Invoke(System.Windows.Threading.DispatcherPriority.Normal, PostMessage, new Object(), e);
                //    return;
                //}

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

        private void GetsWeigth()
        {
            //Запускаем подключение

            foreach (ScalesUnit elem in _tableUnit)
            {
                try
                {
                    elem.ConnectBd();
                }
                catch (Exception ex)
                {
                    elem.STATUS = -1;
                    Dispatcher.Invoke(new Action(() =>
                    {
                        SaveLogThread(elem.Name + ":" + elem.IP_BD, ex.Message, -1);
                    }));
                }

            }


            while (TreadServiceWork)
            {


                foreach (ScalesUnit elem in _tableUnit)
                {
                    try
                    {
                        elem.GetWigth();
                    }

                    catch (Exception ex)
                    {
                        Dispatcher.Invoke(new Action(() =>
                        {

                            SaveLogThread(elem.Name + ":" + elem.IP_BD, ex.Message, -1);
                        }));


                        //Если все плохо

                        try
                        {
                            Dispatcher.Invoke(new Action(() =>
                            {

                                SaveLogThread(elem.Name + ":" + elem.IP_BD, "Переподключаемся", -1);
                            }));

                            Thread.Sleep(2000);

                            elem.ConnectBd();

                        }

                        catch (Exception eee)
                        {
                            Dispatcher.Invoke(new Action(() =>
                            {

                                SaveLogThread(elem.Name + ":" + elem.IP_BD, eee.Message, -1);
                            }));

                        }
                    }
                }
                // SaveLogThread("System", "Check", 0);
                Thread.Sleep(2000);

            }

            foreach (ScalesUnit elem in _tableUnit)
            {
                try
                {
                    elem.CloseConn();
                }

                catch (Exception ex)
                {
                    Dispatcher.Invoke(new Action(() =>
                    {
                        SaveLogThread(elem.Name + ":" + elem.IP_BD, ex.Message, -1);
                    }));

                }
            }

        }


        private void CheckWorked()
        {
            //Тут будет небольшая задержка
            Thread.Sleep(10);

            while (CheckWorkedBool)
            {
                //Алгоритм записи во временный файл
                try
                {
                    StreamWriter sw = new StreamWriter("DataScales-KeepAlive.lock", false, Encoding.GetEncoding(1251));
                    String temp_str = DateTime.Now.ToString();
                    sw.WriteLine(temp_str);
                    sw.Close();

                }

                catch (Exception e5)
                {

                }

                Thread.Sleep(200);
            }

        }

        private void SendOracle()
        {
            try
            {
                //Запускаем подключение
                string _DataSource = "kkcdbpr";
                string _Login = "mts_scales";
                string _Password = "mtsscales";
                OracleConnection appConn;
                OracleCommand cmd;

                string StringConnection = "Data Source=" + _DataSource + ";User Id=" + _Login + ";Password=" + _Password + ";";
                appConn = new OracleConnection(StringConnection);
                appConn.Open();



                while (TreadOracleWork)
                {
                    Dispatcher.Invoke(new Action(() =>
                    {
                        OracleUpdate.Text = "Oracle Send: " + DateTime.Now.ToString() + " CountBuf: " + _BuffByOracle.Count.ToString();
                    }));

                    int iUI = 0;

                    try
                    {
                        // foreach (RecordByOracle rec in _BuffByOracle)
                        //{

                        for (int i = 0; i < _BuffByOracle.Count; i++)
                        {
                            var rec = _BuffByOracle[i];
                            iUI++;
                            if (iUI % 10 == 0)
                            {//Визуализируем процесс
                                Int32 R = _BuffByOracle.Count - iUI;

                                Dispatcher.Invoke(new Action(() =>
                                {
                                    OracleUpdate.Text = "Oracle Send: " + DateTime.Now.ToString() + " CountBuf: " + R.ToString();
                                }));

                            }

                            if (!rec.write)
                            {
                                try
                                {
                                    if (appConn.State != ConnectionState.Open)
                                    {
                                        try
                                        {
                                            SaveLogThread("Oracle_Restart", "No Open Curs", -1);
                                            appConn = new OracleConnection(StringConnection);
                                            appConn.Open();
                                        }

                                        catch (Exception eee)
                                        {

                                            SaveLogThread("Oracle_Exp_Restart", eee.Message, -1);
                                        }

                                    }

                                    cmd = appConn.CreateCommand();
                                    cmd.Parameters.Clear();
                                    cmd.CommandText = "vesy_zap_dblink.save_ves";
                                    cmd.CommandType = System.Data.CommandType.StoredProcedure;
                                    cmd.Parameters.Add("vesy_nom_", OracleType.VarChar).Value = rec.Nom;
                                    cmd.Parameters.Add("vesy_name_", OracleType.VarChar).Value = rec.Name;
                                    cmd.Parameters.Add("vesy_vesnum_", OracleType.VarChar).Value = rec.Weigth;
                                    cmd.Parameters.Add("vesy_dnsname_", OracleType.VarChar).Value = "AMT_DATASCALES";
                                    cmd.Parameters.Add("vesy_datetime_", OracleType.VarChar).Value = rec.DateWeigth;
                                    cmd.Parameters.Add("vesy_ip_", OracleType.VarChar).Value = "127.0.0.1";
                                    cmd.Parameters.Add("vesy_raw_", OracleType.VarChar).Value = rec.raw;

                                    if (rec.RecoverySystem)
                                        cmd.Parameters.Add("check_history_", OracleType.Int32).Value = 1;



                                    cmd.ExecuteNonQuery();
                                    rec.write = true;

                                }

                                catch (OracleException exx)
                                {
                                    SaveLogThread("Oracle_ORA", exx.Message, -1);
                                    //Пробуем перезапустить подключение.

                                    try
                                    {
                                        appConn = new OracleConnection(StringConnection);
                                        appConn.Open();
                                    }

                                    catch (Exception eee)
                                    {

                                        SaveLogThread("Oracle_Exp_Restart", eee.Message, -1);
                                    }
                                }

                                catch (Exception ex)
                                {
                                    SaveLogThread("Oracle_Exp", ex.Message, -1);

                                    Thread.Sleep(1000);
                                    //Запись должна произойти 
                                    ///rec.write = true;
                                }
                            }
                        }

                    }
                    catch (Exception ex)
                    {
                        Thread.Sleep(2000);
                        SaveLogThread("OracleFor", ex.Message, -1);
                    }


                    try
                    {
                        for (int i = 0; i < _BuffByOracle.Count; i++)

                            if (_BuffByOracle[i].write)
                                _BuffByOracle.RemoveAt(i);

                    }
                    catch (Exception ex)
                    {
                        Thread.Sleep(2000);
                        SaveLogThread("Oracle1", ex.Message, -1);
                    }


                }

                appConn.Close();

            }

            catch (Exception ex)
            {
                SaveLogThread("Oracle2", ex.Message, -1);
            }
        }


        public class ScalesUnit : INotifyPropertyChanged
        {
            public event PropertyChangedEventHandler PropertyChanged;

            public string NUM_PP { get; set; }
            public string Name { get; set; }
            public string IP_BD { get; set; }
            public string TIME_CHECK
            {
                get
                {
                    return time_check;
                }
                set
                {
                    time_check = value;
                    OnPropertyChanged("time_check");
                }

            }

            private string time_check;

            public string TIME_ORACLE
            {
                get
                {
                    return time_oracle;
                }
                set
                {
                    time_oracle = value;
                    OnPropertyChanged("TIME_ORACLE");
                }

            }

            private string time_oracle;


            public string TIME_WIGTH
            {
                get
                {
                    return time_weigth;
                }
                set
                {
                    time_weigth = value;
                    OnPropertyChanged("TIME_WIGTH");
                }

            }

            private string time_weigth;

            public string WIGTH
            {
                get
                {
                    return weigth;
                }
                set
                {
                    weigth = value;
                    OnPropertyChanged("WIGTH");

                }

            }

            private string weigth;


            public string RAW
            {
                get
                {
                    return raw;
                }
                set
                {
                    raw = value;
                    OnPropertyChanged("raw");
                    OnPropertyChanged("WIGTH");
                }

            }

            private string raw;

            public int STATUS
            {
                get
                {
                    return status;
                }
                set
                {
                    status = value;
                    OnPropertyChanged("status");
                    OnPropertyChanged("Background");
                }

            }

            private int status;

            public SolidColorBrush Background
            {
                get
                {

                    if (STATUS == 1)
                        return new SolidColorBrush(Colors.WhiteSmoke);

                    else if (STATUS == -1)
                        return new SolidColorBrush(Colors.Tomato);

                    else
                        return new SolidColorBrush(Colors.Yellow);


                }

                set
                {
                    Background = value;
                }
            }



            protected void OnPropertyChanged(string name)
            {
                PropertyChangedEventHandler handler = PropertyChanged;
                if (handler != null)
                {
                    handler(this, new PropertyChangedEventArgs(name));
                }
            }

            private SqlConnection conn = null;


            public void ConnectBd()
            {

                try
                {
                    CloseConn();
                    Thread.Sleep(1);
                }

                catch
                {

                }
                finally
                {
                    conn = null;
                    Thread.Sleep(1);
                }

                if ((conn == null) || (STATUS == -1))
                {
                    string connt = "Data Source=" + IP_BD + "\\SQLEXPRESS; Initial Catalog = vrt_base; User ID=AMT;Password=AMT";
                    conn = new SqlConnection(@connt);
                    //try
                    //{
                    conn.Open();
                    // Label7.Text = "Connection Open ! ";
                    //SaveLog(Name + ":" + IP_BD, "Подключение Ok", 1);
                    //cnn.Close();
                    STATUS = 1;
                    //}
                    //catch (Exception ex)
                    //{
                    //    // Label8.Text = "Can not open connection ! ";
                    //    SaveLog(Name + ":" + IP_BD, ex.Message, -1);
                    //    STATUS = -1;
                    //    return;

                    //}
                }
            }

            private List<List<string>> buff_old = new List<List<string>>();
            private List<List<string>> buff = new List<List<string>>();
            public void GetWigth()
            {
                buff = new List<List<string>>();

                if ((STATUS == -1) || (conn == null))
                {
                    try
                    {
                        ConnectBd();
                    }

                    catch (Exception ex)
                    {
                        Thread.Sleep(1);
                    }


                    return;

                }




                bool RecoverySystem = false;
                int CountRec = 10;
                if (buff_old.Count == 0)
                {
                    CountRec = 1000;
                    RecoverySystem = true;

                }

                SqlCommand cmd = new SqlCommand("Select TOP " + CountRec.ToString() + " * From fixed order by MODIFY_DATE desc", conn);

                // RAW = "test";
                // TIME_WIGTH = "TST";
                //using ()
                //{
                SqlDataReader dr = cmd.ExecuteReader();
                if (dr.Read())
                {

                    string Tmp_TIME_CHECK = DateTime.Now.ToString();
                    string Tmp_TIME_WIGTH = dr.GetValue(1).ToString().Trim();
                    string Tmp_WIGTH = dr.GetValue(7).ToString().Trim();


                    string tmp_slab_num;
                    try
                    {
                        tmp_slab_num = dr.GetValue(14).ToString().Trim();

                        string pattern = @"(\w)";
                        Regex regex = new Regex(pattern);
                        Match match = regex.Match(tmp_slab_num);

                        // отображаем все совпадения
                        tmp_slab_num = "";
                        while (match.Success)
                        {
                            // Т.к. мы выделили в шаблоне одну группу (одни круглые скобки),
                            // ссылаемся на найденное значение через свойство Groups класса Match
                            //Console.WriteLine(match.Groups[1].Value);

                            // Переходим к следующему совпадению
                            tmp_slab_num += match.Groups[0].ToString();
                            match = match.NextMatch();

                        }
                    }

                    catch
                    {
                        tmp_slab_num = dr.GetValue(14).ToString().Trim() + "Ex";
                    }


                    string Tmp_RAW = "SLYAB_ID=" + dr.GetValue(15).ToString().Trim() + ";PLAVKA_NUM=" + dr.GetValue(16).ToString().Trim() + ";SLYAB_NUM=" + tmp_slab_num + ";";

                    try
                    {
                        Double R = Double.Parse(Tmp_WIGTH) / 1000;
                        Tmp_WIGTH = R.ToString();
                    }

                    catch { }


                    TIME_CHECK = Tmp_TIME_CHECK;
                    TIME_WIGTH = Tmp_TIME_WIGTH;
                    WIGTH = Tmp_WIGTH;
                    RAW = Tmp_RAW;



                    List<string> tmp_b = new List<string>();
                    tmp_b.Add(Tmp_TIME_CHECK);
                    tmp_b.Add(Tmp_TIME_WIGTH);
                    tmp_b.Add(Tmp_WIGTH);
                    tmp_b.Add(Tmp_RAW);
                    buff.Add(tmp_b);

                }

                while (dr.Read())
                {
                    string Tmp_TIME_CHECK = DateTime.Now.ToString();
                    string Tmp_TIME_WIGTH = dr.GetValue(1).ToString().Trim();
                    string Tmp_WIGTH = dr.GetValue(7).ToString().Trim();

                    string tmp_slab_num;
                    try
                    {
                        tmp_slab_num = dr.GetValue(14).ToString().Trim();

                        string pattern = @"(\w)";
                        Regex regex = new Regex(pattern);
                        Match match = regex.Match(tmp_slab_num);

                        // отображаем все совпадения
                        tmp_slab_num = "";
                        while (match.Success)
                        {
                            // Т.к. мы выделили в шаблоне одну группу (одни круглые скобки),
                            // ссылаемся на найденное значение через свойство Groups класса Match
                            //Console.WriteLine(match.Groups[1].Value);

                            // Переходим к следующему совпадению
                            tmp_slab_num += match.Groups[0].ToString();
                            match = match.NextMatch();

                        }
                    }

                    catch
                    {
                        tmp_slab_num = dr.GetValue(14).ToString().Trim() + "Ex";
                    }



                    string Tmp_RAW = "SLYAB_ID=" + dr.GetValue(15).ToString().Trim() + ";PLAVKA_NUM=" + dr.GetValue(16).ToString().Trim() + ";SLYAB_NUM=" + tmp_slab_num + ";";


                    try
                    {
                        Double R = Double.Parse(Tmp_WIGTH) / 1000;
                        Tmp_WIGTH = R.ToString();
                    }

                    catch { }

                    List<string> tmp_b = new List<string>();
                    tmp_b.Add(Tmp_TIME_CHECK);
                    tmp_b.Add(Tmp_TIME_WIGTH);
                    tmp_b.Add(Tmp_WIGTH);
                    tmp_b.Add(Tmp_RAW);
                    buff.Add(tmp_b);
                }

                dr.Close();
                // }

                //Выполним сравнение буфера со страым! Все отличия отправим буфер для записи!
                if (buff_old.Count == 0)
                {//Первый запуск

                    foreach (var elem in buff)
                    {
                        RecordByOracle rec = new RecordByOracle(NUM_PP, Name, DateTime.Parse(elem[1]), elem[2], elem[3], RecoverySystem);
                        _BuffByOracle.Add(rec);
                    }
                    buff_old = buff;
                }

                else
                {//Если буфер не пустой
                    //Сравним новый и старый
                    foreach (var elem in buff)
                    {
                        bool Send = true;
                        foreach (var e in buff_old)
                        {
                            if (elem[1] == e[1])
                            {
                                Send = false;
                                break;
                            }
                        }

                        if (Send)
                        {
                            RecordByOracle rec = new RecordByOracle(NUM_PP, Name, DateTime.Parse(elem[1]), elem[2], elem[3]);
                            _BuffByOracle.Add(rec);
                        }
                    }


                    buff_old = buff;
                }
            }




            public void CloseConn()
            {
                try
                {
                    if (conn != null)
                    {
                        conn.Close();
                        //conn.Dispose();
                        //SaveLog(Name + ":" + IP_BD, "Отключение Ok", 1);
                        STATUS = -1;

                        conn = null;
                    }
                }

                catch (Exception ee)
                {
                    //Dispatcher.Invoke(new Action(() =>
                    //{
                    //    SaveLogThread(elem.Name + ":" + elem.IP_BD, ex.Message, -1);
                    //}));
                }
            }

        }

        private void Window_Closed_1(object sender, EventArgs e)
        {
            TreadServiceWork = false;

            TreadService.Abort();

            TreadOracleWork = false;
            TreadOracle.Abort();

            CheckWorkedBool = false;
            CheckWorkedThread.Abort();
        }


        public class RecordByOracle
        {
            public string Nom { get; set; }
            public string Name { get; set; }
            public DateTime DateWeigth { get; set; }
            public string Weigth { get; set; }
            public string raw { get; set; }
            public bool write { get; set; }
            public bool RecoverySystem { get; set; }

            public RecordByOracle(string Nom_, string Name_, DateTime DateWeigth_, string Weigth_, string raw_, bool RecoverySystem_ = false)
            {
                Nom = Nom_;
                Name = Name_;
                DateWeigth = DateWeigth_;
                Weigth = Weigth_;
                raw = raw_;
                write = false;
                RecoverySystem = RecoverySystem_;

            }
        }


    }
}
