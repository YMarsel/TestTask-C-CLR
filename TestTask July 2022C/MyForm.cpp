#include "MyForm.h"
#include <ctime>
#define _USE_MATH_DEFINES
#include <cmath>
#include <exception>

using namespace System;
using namespace System::Windows::Forms;
[STAThreadAttribute]

void Main(array<String^>^ args)
{
    Application::EnableVisualStyles();
    Application::SetCompatibleTextRenderingDefault(false);
    TestTaskJuly2022C::MyForm form;
    Application::Run(% form);
}

//Метод, инициализирующий входные данные по умолчанию (для случая, когда пользователь ничего не ввёл)
void TestTaskJuly2022C::MyForm::DefaultParams()
{
    ampl = 100;         //амплитуда 100 В
    freq = 1;           //частота 1 Гц
    step = 0.1 / freq;  //расчитываем шаг
}

//Событие, вызываемое прокруткой колеса мыши в области графика
System::Void TestTaskJuly2022C::MyForm::chart1_MouseWheel(System::Object^ sender, MouseEventArgs^ e)
{
    if (e->Delta < 0) //Прокрутка вниз
    {
        chart1->ChartAreas[0]->AxisX->ScaleView->ZoomReset();
        chart1->ChartAreas[0]->AxisY->ScaleView->ZoomReset();
    }
    else if (e->Delta > 0) //Прокрутка вверх
    {
        try 
        {
            double xMin = chart1->ChartAreas[0]->AxisX->ScaleView->ViewMinimum;
            double xMax = chart1->ChartAreas[0]->AxisX->ScaleView->ViewMaximum;
            double yMin = chart1->ChartAreas[0]->AxisY->ScaleView->ViewMinimum;
            double yMax = chart1->ChartAreas[0]->AxisY->ScaleView->ViewMaximum;

            double posXStart = chart1->ChartAreas[0]->AxisY->PixelPositionToValue(e->Location.X / 2) - (xMax - xMin) / 4;
            double posXFinish = chart1->ChartAreas[0]->AxisY->PixelPositionToValue(e->Location.X / 2) + (xMax - xMin) / 4;

            double posYStart = chart1->ChartAreas[0]->AxisY->PixelPositionToValue(e->Location.Y) - (yMax - yMin) / 4;
            double posYFinish = chart1->ChartAreas[0]->AxisY->PixelPositionToValue(e->Location.Y) + (yMax - yMin) / 4;

            chart1->ChartAreas[0]->AxisX->ScaleView->Zoom(posXStart, posXFinish);
            chart1->ChartAreas[0]->AxisY->ScaleView->Zoom(posYStart, posYFinish);
        }
        catch (System::ArgumentException^ e) 
        {
            
        }
    }
    return System::Void();
}

//Событие, вызываемое нахождением курсора над областью графика
System::Void TestTaskJuly2022C::MyForm::chart1_MouseMove(System::Object^ sender, MouseEventArgs^ e)
{
    if (isLeftButtonPressed)
    {
        //находим позицию клика в области графика
        System::Windows::Forms::DataVisualization::Charting::HitTestResult^ result = chart1->HitTest(e->X, e->Y);
        if (result->ChartElementType == System::Windows::Forms::DataVisualization::Charting::ChartElementType::PlottingArea)
        {
            //рассчёт изменения координат курсора
            double oldXValue = result->ChartArea->AxisX->PixelPositionToValue(mouseDown.X);
            double newXValue = result->ChartArea->AxisX->PixelPositionToValue(e->X);
            double oldYValue = result->ChartArea->AxisY->PixelPositionToValue(mouseDown.Y);
            double newYValue = result->ChartArea->AxisY->PixelPositionToValue(e->Y);

            //изменение видимой области графика на основе раннее сделанных рассчётов
            chart1->ChartAreas[0]->AxisX->ScaleView->Position += oldXValue - newXValue;
            chart1->ChartAreas[0]->AxisY->ScaleView->Position += oldYValue - newYValue;
            mouseDown.Y = e->Y;
            mouseDown.X = e->X;
        }
    }
    return System::Void();
}

//пользователь отпустил левую кнопку мыши
System::Void TestTaskJuly2022C::MyForm::chart1_MouseUp(System::Object^ sender, MouseEventArgs^ e)
{
    if (e->Button == System::Windows::Forms::MouseButtons::Left)
    {
        isLeftButtonPressed = false;
        mouseDown = Point::Empty;
    }
    return System::Void();
}

//пользователь нажал/зажал левую кнопку мыши
System::Void TestTaskJuly2022C::MyForm::chart1_MouseDown(System::Object^ sender, MouseEventArgs^ e)
{
    if (e->Button == System::Windows::Forms::MouseButtons::Left)
    {
        isLeftButtonPressed = true;
        mouseDown = e->Location;
    }
    return System::Void();
}

//загрузка графика
System::Void TestTaskJuly2022C::MyForm::открытьToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e)
{
    //открытие файлового диалог. окна с заданными параметрами
    OpenFileDialog^ openFileDialog1 = gcnew OpenFileDialog();
    openFileDialog1->InitialDirectory = "C:/Users//Documents";
    openFileDialog1->Filter = "txt files (*.txt)|*.txt|All files (*.*)|*.*";
    openFileDialog1->FilterIndex = 2;
    openFileDialog1->RestoreDirectory = true;

    //если пользователь выбрал файл нажал "ОК"
    if (openFileDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK)
    {
        //десериализирование списка с точками и запись данных в основной список для хранения коллекции точек
        System::Xml::Serialization::XmlSerializer^ xmls = gcnew System::Xml::Serialization::XmlSerializer(list->GetType());
        System::IO::FileStream^ fs = gcnew System::IO::FileStream(openFileDialog1->FileName, System::IO::FileMode::Open);
        list = (Generic::List<PointF>^) xmls->Deserialize(fs);
        fs->Close(); //обязательно закрыть поток

        //в механизм сохранения встроенно сохранение параметров графика "в хвосте" списка перед его сериализацией
        ampl = list[list->Count - 1].X;     //загрузка амплитуды
        freq = list[list->Count - 1].Y;     //загрузка частоты
        list->RemoveAt(list->Count - 1);    //удаление ячейки с параметрами графика

        //передача видимой части графика изменившихся после загрузки параметров (максимум и минимум по амплитуде)
        chart1->ChartAreas[0]->AxisY->Maximum = ampl;
        chart1->ChartAreas[0]->AxisY->Minimum = -ampl;
        chart1->ChartAreas[0]->AxisY->Interval = ampl / 10;
        
        x = list[list->Count - 1].X;        //инициализируем Х из списка
        step = list[list->Count - 1].X - list[list->Count - 2].X; //инициализируем шаг из списка

        //обновление области графика
        chart1->Refresh();

        //выставление границ
        chart1->ChartAreas[0]->AxisX->Minimum = x - step * 30;
        chart1->ChartAreas[0]->AxisX->Maximum = x;
        
        //привязка графика к списку точек
        chart1->Series[0]->XValueMember = "X";
        chart1->Series[0]->YValueMembers = "Y";
        chart1->DataSource = list;
        chart1->DataBind();

        //разблокировка кнопки "Старт"
        button_start->Enabled = true;
    }
    return System::Void();
}

System::Void TestTaskJuly2022C::MyForm::сохранитьToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e)
{
    //создание уникального имени файла с помощью времени
    time_t now = time(0);
    String^ fileName("Sinus Signal Graph  " + Convert::ToString(now));

    //инициализация файлового диалог. окна с заданными параметрами
    SaveFileDialog^ saveFileDialog1 = gcnew SaveFileDialog();
    saveFileDialog1->Filter = "TextFiles (*.txt)|*.txt|All files(*.*)|*.*";
    saveFileDialog1->FilterIndex = 1;
    saveFileDialog1->RestoreDirectory = true;
    saveFileDialog1->CreatePrompt = true;
    saveFileDialog1->OverwritePrompt = true;
    saveFileDialog1->FileName = fileName;
    saveFileDialog1->InitialDirectory = "C:/Users//Documents";

    //если пользователь выбрал директорию и нажал "ОК"
    if (saveFileDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK)
    {
        //"заморозка" таймера, чтобы он не повлиял на сохраняемый список
        timer1->Enabled = false;

        //добавление параметров графика в конец списка
        list->Add(PointF(ampl, freq));

        //сериализация списка и его сохранение в текстовый файл
        System::Xml::Serialization::XmlSerializer^ xmls = gcnew System::Xml::Serialization::XmlSerializer(list->GetType());
        System::IO::FileStream^ fs = gcnew System::IO::FileStream(saveFileDialog1->FileName, System::IO::FileMode::Create);
        xmls->Serialize(fs, list);
        fs->Close(); //обязательно закрыть поток
        list->RemoveAt(list->Count - 1); //удаление ячейки, содержащей параметры графика
    }
    return System::Void();
}

//событие нажатия кнопки "Принять"
System::Void TestTaskJuly2022C::MyForm::button_applyData_Click(System::Object^ sender, System::EventArgs^ e)
{
    //т.к. ввести пользователь может несколько наборов данных за один запуск программы, необходимо отчищать область графика и обновлять её
    chart1->Series[0]->XValueMember = "X";
    chart1->Series[0]->YValueMembers = "Y";
    list->Clear();
    chart1->Refresh();
    chart1->DataSource = list;  //привязка графика к списку


    //Блокируем кнопка старта отрисовки графика, на случай, если после удачного ввода данных, были введены некорректные данные (кнопка старта оставалась активной)
    button_start->Enabled = false;

    //Проверка полей на введенные символы, если пользователь ничего не введет, программа применит данные по умолчанию
    if (String::IsNullOrWhiteSpace(textBox_ampl->Text) || String::IsNullOrWhiteSpace(textBox_freq->Text))
    {
        MessageBox::Show("Введен неполный набор данных, будут применены данные по умолчанию (100 В, 1 Гц).", "Внимание!", MessageBoxButtons::OK, MessageBoxIcon::Warning);
        DefaultParams(); //Применяем данные по умолчанию
        chart1->ChartAreas[0]->AxisY->Maximum = ampl;
        chart1->ChartAreas[0]->AxisY->Minimum = -ampl;
        chart1->ChartAreas[0]->AxisY->Interval = ampl / 10;
        button_start->Enabled = true;   //Данные по умолчанию априори корректны, разблокируем кнопку старта симуляции
        chart1->ChartAreas[0]->AxisX->Minimum = 0;
        chart1->ChartAreas[0]->AxisX->Maximum = step * 30;
    }
    else
    {
        //Если пользователь ввёл некоторые значения в поля. Пытаемся привести тип введенных данных к числу с плавающей запятой двойной точности (double).
        bool correctTypeInput = (System::Double::TryParse(textBox_ampl->Text, ampl) && (System::Double::TryParse(textBox_freq->Text, freq)));

        //если TryParse() для обоих значений вернул true
        if (correctTypeInput)
        {
            //проверяем значения на соответствие их допустимым диапазонам
            if ((freq >= 1) && (freq <= 100) && (ampl >= 100) && (ampl <= 10000))
            {
                //если значения соответствуют диапазонам, разблокируем кнопку старта симуляции
                step = 0.1 / freq;
                button_start->Enabled = true;
                chart1->ChartAreas[0]->AxisY->Maximum = ampl;
                chart1->ChartAreas[0]->AxisY->Minimum = -ampl;
                chart1->ChartAreas[0]->AxisY->Interval = ampl / 10;
                chart1->ChartAreas[0]->AxisX->Minimum = 0;
                chart1->ChartAreas[0]->AxisX->Maximum = step * 30;
            }
            //если введенные значения вне допустимого диапазона
            else
            {
                //сообщаем пользователю об ошибке и очищаем поля для ввода
                MessageBox::Show("Введены неверные входные данные! (Значения введенных данных не соответствуют требуемым!)", "Ошибка!", MessageBoxButtons::OK, MessageBoxIcon::Warning);
                textBox_ampl->Clear();
                textBox_freq->Clear();
            }
        }
        //если TryParse() хотя бы одного из значений вернул false
        else
        {
            //сообщаем пользователю об ошибке и очищаем поля для ввода
            MessageBox::Show("Введены неверные входные данные! (Тип введенных данных не соответствует требуемуму!)", "Ошибка!", MessageBoxButtons::OK, MessageBoxIcon::Warning);
            textBox_ampl->Clear();
            textBox_freq->Clear();
        }
    }
    return System::Void();
}

//событие нажатия кнопки "Старт"
System::Void TestTaskJuly2022C::MyForm::button_start_Click(System::Object^ sender, System::EventArgs^ e)
{
    //разморозка таймера
    timer1->Enabled = true;

    //изменение доступности кнопок
    button_applyData->Enabled = false;
    button_stop->Enabled = true;
    button_start->Enabled = false;
    button_allGraphVisiblity->Enabled = false;
    
    return System::Void();
}

//событие нажатия кнопки "Стоп"
System::Void TestTaskJuly2022C::MyForm::button_stop_Click(System::Object^ sender, System::EventArgs^ e)
{
    //замораживаем таймер
    timer1->Enabled = false;

    //изменение доступности кнопок
    button_applyData->Enabled = true;
    button_stop->Enabled = false;
    button_start->Enabled = true;
    button_allGraphVisiblity->Enabled = true;

    return System::Void();
}

//событие тика таймера
System::Void TestTaskJuly2022C::MyForm::timer1_Tick(System::Object^ sender, System::EventArgs^ e)
{
    y = ampl * sin(2 * M_PI * x * freq);    //расчёт точки Y
    list->Add(PointF(x, y));                //добавление в список точки (x, y), в параметрах float числа   
    
    //"обновление" значений, отображаемые на графике
    chart1->DataBind();

    //смещение границ отображения графика, т.к. step = 0.1 * freq, в одном периоде синусоиды 10 точек, следовательно step * 30 - три периода
    chart1->ChartAreas[0]->AxisX->Minimum = x - step * 30;
    chart1->ChartAreas[0]->AxisX->Maximum = x;

    x += step;  //изменяем Х
    return System::Void();
}

//событие нажатия на кнопку "Отобразить график"
System::Void TestTaskJuly2022C::MyForm::button_allGraphVisiblity_Click(System::Object^ sender, System::EventArgs^ e)
{
    chart1->ChartAreas[0]->AxisX->Minimum = 0; //сброс видимой границы до нуля
    return System::Void();
}

//о программе
System::Void TestTaskJuly2022C::MyForm::оПрограммеToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e)
{
    MessageBox::Show("Тестовое задание на вакансию Стажера С++.\nВыполнил Марсель Ягудин.\nСамара, 2022 год.","О программе", MessageBoxButtons::OK, MessageBoxIcon::Information);
    return System::Void();
}

//выход
System::Void TestTaskJuly2022C::MyForm::выходToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e)
{
    if (MessageBox::Show("Вы действительно хотите выйти? Все несохраненные данные будут утеряны.", "Выход", 
        MessageBoxButtons::OKCancel, MessageBoxIcon::Warning) == Windows::Forms::DialogResult::OK)
    {
        Application::Exit();
    }
    return System::Void();
}

