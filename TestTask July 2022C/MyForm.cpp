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

//�����, ���������������� ������� ������ �� ��������� (��� ������, ����� ������������ ������ �� ���)
void TestTaskJuly2022C::MyForm::DefaultParams()
{
    ampl = 100;         //��������� 100 �
    freq = 1;           //������� 1 ��
    step = 0.1 / freq;  //����������� ���
}

//�������, ���������� ���������� ������ ���� � ������� �������
System::Void TestTaskJuly2022C::MyForm::chart1_MouseWheel(System::Object^ sender, MouseEventArgs^ e)
{
    if (e->Delta < 0) //��������� ����
    {
        chart1->ChartAreas[0]->AxisX->ScaleView->ZoomReset();
        chart1->ChartAreas[0]->AxisY->ScaleView->ZoomReset();
    }
    else if (e->Delta > 0) //��������� �����
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

//�������, ���������� ����������� ������� ��� �������� �������
System::Void TestTaskJuly2022C::MyForm::chart1_MouseMove(System::Object^ sender, MouseEventArgs^ e)
{
    if (isLeftButtonPressed)
    {
        //������� ������� ����� � ������� �������
        System::Windows::Forms::DataVisualization::Charting::HitTestResult^ result = chart1->HitTest(e->X, e->Y);
        if (result->ChartElementType == System::Windows::Forms::DataVisualization::Charting::ChartElementType::PlottingArea)
        {
            //������� ��������� ��������� �������
            double oldXValue = result->ChartArea->AxisX->PixelPositionToValue(mouseDown.X);
            double newXValue = result->ChartArea->AxisX->PixelPositionToValue(e->X);
            double oldYValue = result->ChartArea->AxisY->PixelPositionToValue(mouseDown.Y);
            double newYValue = result->ChartArea->AxisY->PixelPositionToValue(e->Y);

            //��������� ������� ������� ������� �� ������ ������ ��������� ���������
            chart1->ChartAreas[0]->AxisX->ScaleView->Position += oldXValue - newXValue;
            chart1->ChartAreas[0]->AxisY->ScaleView->Position += oldYValue - newYValue;
            mouseDown.Y = e->Y;
            mouseDown.X = e->X;
        }
    }
    return System::Void();
}

//������������ �������� ����� ������ ����
System::Void TestTaskJuly2022C::MyForm::chart1_MouseUp(System::Object^ sender, MouseEventArgs^ e)
{
    if (e->Button == System::Windows::Forms::MouseButtons::Left)
    {
        isLeftButtonPressed = false;
        mouseDown = Point::Empty;
    }
    return System::Void();
}

//������������ �����/����� ����� ������ ����
System::Void TestTaskJuly2022C::MyForm::chart1_MouseDown(System::Object^ sender, MouseEventArgs^ e)
{
    if (e->Button == System::Windows::Forms::MouseButtons::Left)
    {
        isLeftButtonPressed = true;
        mouseDown = e->Location;
    }
    return System::Void();
}

//�������� �������
System::Void TestTaskJuly2022C::MyForm::�������ToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e)
{
    //�������� ��������� ������. ���� � ��������� �����������
    OpenFileDialog^ openFileDialog1 = gcnew OpenFileDialog();
    openFileDialog1->InitialDirectory = "C:/Users//Documents";
    openFileDialog1->Filter = "txt files (*.txt)|*.txt|All files (*.*)|*.*";
    openFileDialog1->FilterIndex = 2;
    openFileDialog1->RestoreDirectory = true;

    //���� ������������ ������ ���� ����� "��"
    if (openFileDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK)
    {
        //������������������ ������ � ������� � ������ ������ � �������� ������ ��� �������� ��������� �����
        System::Xml::Serialization::XmlSerializer^ xmls = gcnew System::Xml::Serialization::XmlSerializer(list->GetType());
        System::IO::FileStream^ fs = gcnew System::IO::FileStream(openFileDialog1->FileName, System::IO::FileMode::Open);
        list = (Generic::List<PointF>^) xmls->Deserialize(fs);
        fs->Close(); //����������� ������� �����

        //� �������� ���������� ��������� ���������� ���������� ������� "� ������" ������ ����� ��� �������������
        ampl = list[list->Count - 1].X;     //�������� ���������
        freq = list[list->Count - 1].Y;     //�������� �������
        list->RemoveAt(list->Count - 1);    //�������� ������ � ����������� �������

        //�������� ������� ����� ������� ������������ ����� �������� ���������� (�������� � ������� �� ���������)
        chart1->ChartAreas[0]->AxisY->Maximum = ampl;
        chart1->ChartAreas[0]->AxisY->Minimum = -ampl;
        chart1->ChartAreas[0]->AxisY->Interval = ampl / 10;
        
        x = list[list->Count - 1].X;        //�������������� � �� ������
        step = list[list->Count - 1].X - list[list->Count - 2].X; //�������������� ��� �� ������

        //���������� ������� �������
        chart1->Refresh();

        //����������� ������
        chart1->ChartAreas[0]->AxisX->Minimum = x - step * 30;
        chart1->ChartAreas[0]->AxisX->Maximum = x;
        
        //�������� ������� � ������ �����
        chart1->Series[0]->XValueMember = "X";
        chart1->Series[0]->YValueMembers = "Y";
        chart1->DataSource = list;
        chart1->DataBind();

        //������������� ������ "�����"
        button_start->Enabled = true;
    }
    return System::Void();
}

System::Void TestTaskJuly2022C::MyForm::���������ToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e)
{
    //�������� ����������� ����� ����� � ������� �������
    time_t now = time(0);
    String^ fileName("Sinus Signal Graph  " + Convert::ToString(now));

    //������������� ��������� ������. ���� � ��������� �����������
    SaveFileDialog^ saveFileDialog1 = gcnew SaveFileDialog();
    saveFileDialog1->Filter = "TextFiles (*.txt)|*.txt|All files(*.*)|*.*";
    saveFileDialog1->FilterIndex = 1;
    saveFileDialog1->RestoreDirectory = true;
    saveFileDialog1->CreatePrompt = true;
    saveFileDialog1->OverwritePrompt = true;
    saveFileDialog1->FileName = fileName;
    saveFileDialog1->InitialDirectory = "C:/Users//Documents";

    //���� ������������ ������ ���������� � ����� "��"
    if (saveFileDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK)
    {
        //"���������" �������, ����� �� �� ������� �� ����������� ������
        timer1->Enabled = false;

        //���������� ���������� ������� � ����� ������
        list->Add(PointF(ampl, freq));

        //������������ ������ � ��� ���������� � ��������� ����
        System::Xml::Serialization::XmlSerializer^ xmls = gcnew System::Xml::Serialization::XmlSerializer(list->GetType());
        System::IO::FileStream^ fs = gcnew System::IO::FileStream(saveFileDialog1->FileName, System::IO::FileMode::Create);
        xmls->Serialize(fs, list);
        fs->Close(); //����������� ������� �����
        list->RemoveAt(list->Count - 1); //�������� ������, ���������� ��������� �������
    }
    return System::Void();
}

//������� ������� ������ "�������"
System::Void TestTaskJuly2022C::MyForm::button_applyData_Click(System::Object^ sender, System::EventArgs^ e)
{
    //�.�. ������ ������������ ����� ��������� ������� ������ �� ���� ������ ���������, ���������� �������� ������� ������� � ��������� �
    chart1->Series[0]->XValueMember = "X";
    chart1->Series[0]->YValueMembers = "Y";
    list->Clear();
    chart1->Refresh();
    chart1->DataSource = list;  //�������� ������� � ������


    //��������� ������ ������ ��������� �������, �� ������, ���� ����� �������� ����� ������, ���� ������� ������������ ������ (������ ������ ���������� ��������)
    button_start->Enabled = false;

    //�������� ����� �� ��������� �������, ���� ������������ ������ �� ������, ��������� �������� ������ �� ���������
    if (String::IsNullOrWhiteSpace(textBox_ampl->Text) || String::IsNullOrWhiteSpace(textBox_freq->Text))
    {
        MessageBox::Show("������ �������� ����� ������, ����� ��������� ������ �� ��������� (100 �, 1 ��).", "��������!", MessageBoxButtons::OK, MessageBoxIcon::Warning);
        DefaultParams(); //��������� ������ �� ���������
        chart1->ChartAreas[0]->AxisY->Maximum = ampl;
        chart1->ChartAreas[0]->AxisY->Minimum = -ampl;
        chart1->ChartAreas[0]->AxisY->Interval = ampl / 10;
        button_start->Enabled = true;   //������ �� ��������� ������� ���������, ������������ ������ ������ ���������
        chart1->ChartAreas[0]->AxisX->Minimum = 0;
        chart1->ChartAreas[0]->AxisX->Maximum = step * 30;
    }
    else
    {
        //���� ������������ ��� ��������� �������� � ����. �������� �������� ��� ��������� ������ � ����� � ��������� ������� ������� �������� (double).
        bool correctTypeInput = (System::Double::TryParse(textBox_ampl->Text, ampl) && (System::Double::TryParse(textBox_freq->Text, freq)));

        //���� TryParse() ��� ����� �������� ������ true
        if (correctTypeInput)
        {
            //��������� �������� �� ������������ �� ���������� ����������
            if ((freq >= 1) && (freq <= 100) && (ampl >= 100) && (ampl <= 10000))
            {
                //���� �������� ������������� ����������, ������������ ������ ������ ���������
                step = 0.1 / freq;
                button_start->Enabled = true;
                chart1->ChartAreas[0]->AxisY->Maximum = ampl;
                chart1->ChartAreas[0]->AxisY->Minimum = -ampl;
                chart1->ChartAreas[0]->AxisY->Interval = ampl / 10;
                chart1->ChartAreas[0]->AxisX->Minimum = 0;
                chart1->ChartAreas[0]->AxisX->Maximum = step * 30;
            }
            //���� ��������� �������� ��� ����������� ���������
            else
            {
                //�������� ������������ �� ������ � ������� ���� ��� �����
                MessageBox::Show("������� �������� ������� ������! (�������� ��������� ������ �� ������������� ���������!)", "������!", MessageBoxButtons::OK, MessageBoxIcon::Warning);
                textBox_ampl->Clear();
                textBox_freq->Clear();
            }
        }
        //���� TryParse() ���� �� ������ �� �������� ������ false
        else
        {
            //�������� ������������ �� ������ � ������� ���� ��� �����
            MessageBox::Show("������� �������� ������� ������! (��� ��������� ������ �� ������������� ����������!)", "������!", MessageBoxButtons::OK, MessageBoxIcon::Warning);
            textBox_ampl->Clear();
            textBox_freq->Clear();
        }
    }
    return System::Void();
}

//������� ������� ������ "�����"
System::Void TestTaskJuly2022C::MyForm::button_start_Click(System::Object^ sender, System::EventArgs^ e)
{
    //���������� �������
    timer1->Enabled = true;

    //��������� ����������� ������
    button_applyData->Enabled = false;
    button_stop->Enabled = true;
    button_start->Enabled = false;
    button_allGraphVisiblity->Enabled = false;
    
    return System::Void();
}

//������� ������� ������ "����"
System::Void TestTaskJuly2022C::MyForm::button_stop_Click(System::Object^ sender, System::EventArgs^ e)
{
    //������������ ������
    timer1->Enabled = false;

    //��������� ����������� ������
    button_applyData->Enabled = true;
    button_stop->Enabled = false;
    button_start->Enabled = true;
    button_allGraphVisiblity->Enabled = true;

    return System::Void();
}

//������� ���� �������
System::Void TestTaskJuly2022C::MyForm::timer1_Tick(System::Object^ sender, System::EventArgs^ e)
{
    y = ampl * sin(2 * M_PI * x * freq);    //������ ����� Y
    list->Add(PointF(x, y));                //���������� � ������ ����� (x, y), � ���������� float �����   
    
    //"����������" ��������, ������������ �� �������
    chart1->DataBind();

    //�������� ������ ����������� �������, �.�. step = 0.1 * freq, � ����� ������� ��������� 10 �����, ������������� step * 30 - ��� �������
    chart1->ChartAreas[0]->AxisX->Minimum = x - step * 30;
    chart1->ChartAreas[0]->AxisX->Maximum = x;

    x += step;  //�������� �
    return System::Void();
}

//������� ������� �� ������ "���������� ������"
System::Void TestTaskJuly2022C::MyForm::button_allGraphVisiblity_Click(System::Object^ sender, System::EventArgs^ e)
{
    chart1->ChartAreas[0]->AxisX->Minimum = 0; //����� ������� ������� �� ����
    return System::Void();
}

//� ���������
System::Void TestTaskJuly2022C::MyForm::����������ToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e)
{
    MessageBox::Show("�������� ������� �� �������� ������� �++.\n�������� ������� ������.\n������, 2022 ���.","� ���������", MessageBoxButtons::OK, MessageBoxIcon::Information);
    return System::Void();
}

//�����
System::Void TestTaskJuly2022C::MyForm::�����ToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e)
{
    if (MessageBox::Show("�� ������������� ������ �����? ��� ������������� ������ ����� �������.", "�����", 
        MessageBoxButtons::OKCancel, MessageBoxIcon::Warning) == Windows::Forms::DialogResult::OK)
    {
        Application::Exit();
    }
    return System::Void();
}

