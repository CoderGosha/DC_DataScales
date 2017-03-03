using System;
using System.Collections.Generic;
using System.Text;

namespace DataScalesModel
{
    public class Model
    {

        public static List<string> GetListModel()
        {
            //Описываем список всех весов...
            List<string> ret = new List<string>();
            ret.Add("RAW");
            ret.Add("SS_CGP_TCA_50");
            ret.Add("SS_CGP_TBOX_PR1");
            ret.Add("AMT_DISOBOX_PLUS");

            return ret;
        }

        public static ReturnClass RunModel(string Model, string RawString)
        {
            ReturnClass ret = new ReturnClass();
            ret.GoodData = true;
            ret.countClean = RawString.Length - 1;
            switch (Model)
            {
                case "SS_CGP_TCA_50":
                    {
                        ret = Model_SS_CGP_TCA_50(RawString);
                        break;
                    }
                case "SS_CGP_TBOX_PR1":
                    {
                        ret = Model_SS_CGP_TBOX_PR1(RawString);
                        break;
                    }

                case "AMT_DISOBOX_PLUS":
                    {
                        ret = Model_AMT_DISOBOX_PLUS(RawString);
                        break;
                    }
                default:
                    {
                        ret = Model_Raw(RawString);
                        break;
                    }

            }
            return ret;
        }

        public static bool GetSendByteScales(string Model)
        {//Надо ли отправлять байты для запроса...
            bool BReturn = false;
            switch (Model)
            {
                case "AMT_DISOBOX_PLUS":
                    {
                        BReturn = true;
                        break;
                    }
                default:
                    {
                        BReturn = false;
                        break;
                    }

            }
            return BReturn;
        }

        public static Byte[] GetStringForSendScales(string Model)
        {
            Byte[] SReturn = null;
            switch (Model)
            {
                case "AMT_DISOBOX_PLUS":
                    {
                        SReturn = GetStringForSendScales_AMT_DISOBOX_PLUS();
                        break;
                    }
                default:
                    {
                        SReturn = null;
                        break;
                    }

            }
            return SReturn;
        }

        private static Byte[] GetStringForSendScales_AMT_DISOBOX_PLUS()
        {
            Byte[] SReturn;
            string MagicString = "00,00,01,00,00,22,01,55,62,00,04,01,72,70,74,6f,20,6c,23,42,23,34,36,23,31,23,34,30,23,46,46,23,31,23,36,31,21,23,ab,af";
            // string MagicString = "01,";
            string[] STmp = MagicString.Split(',');
            SReturn = new Byte[STmp.Length];
            int ii = 0;
            foreach (string elem in STmp)
            {
                var CTmp = Byte.Parse(elem, System.Globalization.NumberStyles.HexNumber);
                SReturn[ii] = CTmp;
                ii++;
            }
            return SReturn;
        }

        private static ReturnClass Model_SS_CGP_TCA_50(string RawString)
        {
            ReturnClass ret = new ReturnClass();
            ret.GoodData = false;
            ret.rawData = RawString;
            //S  2.030?N
            try
            {
                if (RawString.Length > 10)
                {
                    int StartIndex = RawString.IndexOf("S");
                    int EndIndex = RawString.IndexOf("N", StartIndex);
                    if ((StartIndex != -1) && (EndIndex != -1))
                    {
                        string tmpW = RawString.Substring(StartIndex + 1, 7);
                        ret.weightS = tmpW.Replace(" ", "");

                        //Стабильность
                        if (RawString.Substring(StartIndex + 8, 1) == " ")
                            ret.stabil = true;
                        else
                            ret.stabil = false;

                        ret.rezerv1 = RawString.Substring(StartIndex + 8, 1);

                        ret.countClean = EndIndex + 1;
                        ret.GoodData = true;

                    }
                }
            }

            catch (Exception)
            {

            }
            return ret;
        }

        private static ReturnClass Model_Raw(string RawString)
        {
            ReturnClass ret = new ReturnClass();
            ret.GoodData = true;
            ret.countClean = RawString.Length - 1;
            ret.rawData = RawString;
            ret.weightS = RawString;
            return ret;
        }

        private static ReturnClass Model_SS_CGP_TBOX_PR1(string RawString)
        {
            ReturnClass ret = new ReturnClass();
            ret.GoodData = false;
            ret.rawData = RawString;
            //S  2.030?N
            try
            {
                if (RawString.Length >= 28)
                {
                    //Стартоый символ  S
                    int StartIndex = RawString.IndexOf("S");
                    //Конечный символ 03
                    int EndIndex = RawString.IndexOf(Convert.ToChar(03), StartIndex);

                    if ((StartIndex != -1) && (EndIndex != -1))
                    {
                        string tmpW = RawString.Substring(StartIndex + 2, 6);
                        ret.weightS = tmpW.Replace(" ", "");
                        //Стабильность
                        if (RawString.Substring(StartIndex + 10, 1) == "1")
                            ret.stabil = true;
                        else
                            ret.stabil = false;
                        ret.countClean = EndIndex + 1;
                        ret.GoodData = true;

                    }
                }
            }

            catch (Exception)
            {

            }
            return ret;
        }

        private static ReturnClass Model_AMT_DISOBOX_PLUS(string RawString)
        {
            ReturnClass ret = new ReturnClass();
            ret.GoodData = false;
            ret.rawData = RawString;

            if (RawString.Length >= 100)
            {
                String responseDataHex;
                String responseDataParse;
                String responseDataParseHex;
                Byte[] temp = System.Text.Encoding.UTF8.GetBytes(RawString);
                responseDataHex = BitConverter.ToString(temp);

                ///23-36-31-23- Началов веса
                int i_Begin_H = responseDataHex.IndexOf("23-36-31-23");
                int i_End_H = -1; //Значение по умолчанию
                //int i_len_H = i_End_H - i_Begin_H;

                if (i_Begin_H == -1)
                    ret.GoodData = false;
                else
                {
                    i_End_H = responseDataHex.IndexOf("23", i_Begin_H + 10);
                }

                if (i_End_H == -1)
                    ret.GoodData = false;

                responseDataParseHex = responseDataHex.Substring(i_Begin_H, i_End_H - i_Begin_H);

                responseDataParseHex = responseDataParseHex.Replace("-", String.Empty);
                int i_Begin = 0;
                //int i_End = 0;

                i_Begin = i_Begin_H / 3;
                int i_len_H = responseDataParseHex.Length;

                responseDataParse = RawString.Substring(i_Begin + 4, i_len_H / 2 - 4);


                ///Определим стабильный вес, поиском последовательности

                /* if ((responseDataHex->IndexOf("01-56-61-00") > 0) || (responseDataHex->IndexOf("01-56-5F-00") > 0)){*/
                if (responseDataHex.IndexOf("00-6C-23") > 0)
                {
                    //Стабильный вес
                    ret.stabil = true;
                }
                else
                {
                    ret.stabil = false;
                }

                if (RawString.Length > 0)
                    ret.countClean = 100;
                else
                    ret.countClean = 0;

                ret.rawData = RawString;

                //Конвертнем вес во что то настоящее
                Double w = Double.Parse(responseDataParse.Replace('.', ','));
                w = Math.Round(w, 1);
                ret.weightS = w.ToString().Replace(',', '.');


                ret.GoodData = true;
            }

            return ret;
        }
    }

    public class ReturnClass
    {
        public ReturnClass()
        {
            GoodData = false;
            rawData = null;
            weightS = null;
            weightD = 0;
            stabil = false;
            rezerv1 = null;
            rezerv2 = null;
            rezerv3 = null;
            countClean = 0;
        }
        public bool GoodData;
        public string rawData;
        public string weightS;
        public double weightD;
        public bool stabil;
        public string rezerv1;
        public string rezerv2;
        public string rezerv3;
        public int countClean;
    }
}
