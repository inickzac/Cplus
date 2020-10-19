using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO;
using System.Threading;

namespace CIPHER
{
    public class RC4 
    {

        // Для генерации ключевого потока шифр использует скрытое внутреннее состояние, состоящее из двух частей:
        // Перестановки, содержащей все возможные байты
        //Переменных-счетчиков x и y.

        public event Action<string> secKeyBite;
        public event Action<long[]> ProgressChange;
        byte[] S = new byte[256];

        int x = 0;
        int y = 0;

        public RC4(byte[] key)
        {
            init(key);
        }

        
        // Алгоритм ключевого расписания 
        private void init(byte[] key)
        {
            int keyLength = key.Length;

            for (int i = 0; i < 256; i++)
            {
                S[i] = (byte)i;
            }

            int j = 0;
            for (int i = 0; i < 256; i++)
            {
                j = (j + S[i] + key[i % keyLength]) % 256;
                S.Swap(i, j);
            }
        }

        byte[] Encode(byte[] dataB, int size)
        {
            byte[] data = dataB.Take(size).ToArray();

            byte[] cipher = new byte[data.Length];

            for (int m = 0; m < data.Length; m++)
            {
                cipher[m] = (byte)(data[m] ^ keyItem());
            }

            return cipher;
        }
       byte[] Decode(byte[] dataB, int size)
        {
            return Encode(dataB, size);
        }

       
        
     public  void  CipherFile(string loadFilePath, string saveFileDial, int key)
        {
            FileStream saveFileStream = null;
            FileStream openFileStream = new FileStream(loadFilePath, FileMode.Open, FileAccess.Read, FileShare.None, 100000);
            BinaryReader reader = new BinaryReader(openFileStream);

            long length = new FileInfo(loadFilePath).Length;
            long[] massProcess = new long[3];
            massProcess[0] = openFileStream.Length;
            string extension = Path.GetExtension(loadFilePath);

            if (key == 2 && extension == ".crypt")
            {
                string filePathDecrypt = loadFilePath.Remove(loadFilePath.Length - 6);
                extension = filePathDecrypt.Substring(filePathDecrypt.LastIndexOf("."));
                saveFileStream = new FileStream(saveFileDial + extension, FileMode.Create, FileAccess.Write);
            }

            else

            { saveFileStream = new FileStream(saveFileDial + extension + ".crypt", FileMode.Create, FileAccess.Write); }
            ProgressStr prsttr = new ProgressStr
            {
                massProcess = massProcess,
                openFileStream = openFileStream
            };
            TimerCallback tm = new TimerCallback(CountTimerProgress);
            System.Threading.Timer timerPr = new Timer(tm, prsttr, 0, 20);
            BinaryWriter readerSave = new BinaryWriter(saveFileStream);
            byte[] buffer = new byte[100];
            int bufferSize = buffer.Length;
            while (reader.BaseStream.Position != reader.BaseStream.Length)
            {
                for(int i=0; i<bufferSize; i++)
                {
                    if (reader.BaseStream.Position != reader.BaseStream.Length)
                    {
                        buffer[i] = reader.ReadByte();
                    }
                    else bufferSize = i;
                }
                buffer = Encode(buffer, bufferSize);

                for (int i = 0; i < bufferSize; i++)
                {
                    readerSave.Write(buffer[i]);
                }
            } //Циклически побайтно шифруем или расшифровываем файл
            Thread.Sleep(21);
            timerPr.Dispose();
            openFileStream.Close();
            saveFileStream.Close();
        } //Шифрование и расшифрование файла

        struct ProgressStr //необходимые поля для инициализации строки прогресса
        {
            public long[] massProcess;
            public FileStream openFileStream;
        }

        void CountTimerProgress(object obj) //Метод для инициализации строки прогресса
        {
            ProgressStr massProcess = (ProgressStr)obj;
            massProcess.massProcess[1] = massProcess.openFileStream.Position;
            ProgressChange(massProcess.massProcess);
        }

        private byte keyItem()
        {
            x = (x + 1) % 256;
            y = (y + S[x]) % 256;

            S.Swap(x, y);
            byte key = S[(S[x] + S[y]) % 256];
            secKeyBite(Convert.ToString(key));
            return key;
        }

        
    }

    static class SwapExt
    {
        public static void Swap<T>(this T[] array, int index1, int index2)
        {
            T temp = array[index1];
            array[index1] = array[index2];
            array[index2] = temp;
        }
    }
}
