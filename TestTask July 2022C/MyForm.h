#pragma once

namespace TestTaskJuly2022C {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Сводка для MyForm
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void)
		{
			InitializeComponent();
			//
			//TODO: добавьте код конструктора
			//
		}

	protected:
		/// <summary>
		/// Освободить все используемые ресурсы.
		/// </summary>
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::MenuStrip^ menuStrip1;
	protected:
	private: System::Windows::Forms::ToolStripMenuItem^ файлToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ открытьToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ сохранитьToolStripMenuItem;

	private: System::Windows::Forms::ToolStripMenuItem^ оПрограммеToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ выходToolStripMenuItem;
	private: System::Windows::Forms::GroupBox^ groupBox_data;
	private: System::Windows::Forms::Button^ button_applyData;
	private: System::Windows::Forms::Label^ label_ampl;
	private: System::Windows::Forms::TextBox^ textBox_ampl;
	private: System::Windows::Forms::TextBox^ textBox_freq;
	private: System::Windows::Forms::Label^ label_freq;
	private: System::Windows::Forms::GroupBox^ groupBox_control;
	private: System::Windows::Forms::Button^ button_start;
	private: System::Windows::Forms::Button^ button_stop;
	private: System::Windows::Forms::DataVisualization::Charting::Chart^ chart1;

	private: System::Windows::Forms::Timer^ timer1;
	private: System::Windows::Forms::RichTextBox^ richTextBox1;
	private: System::Windows::Forms::Button^ button_allGraphVisiblity;

	private: System::ComponentModel::IContainer^ components;


	private:
		/// <summary>
		/// Обязательная переменная конструктора.
		/// </summary>


#pragma region Windows Form Designer generated code
		/// <summary>
		/// Требуемый метод для поддержки конструктора — не изменяйте 
		/// содержимое этого метода с помощью редактора кода.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			System::Windows::Forms::DataVisualization::Charting::ChartArea^ chartArea3 = (gcnew System::Windows::Forms::DataVisualization::Charting::ChartArea());
			System::Windows::Forms::DataVisualization::Charting::Legend^ legend3 = (gcnew System::Windows::Forms::DataVisualization::Charting::Legend());
			System::Windows::Forms::DataVisualization::Charting::Series^ series3 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
			this->menuStrip1 = (gcnew System::Windows::Forms::MenuStrip());
			this->файлToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->открытьToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->сохранитьToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->оПрограммеToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->выходToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->groupBox_data = (gcnew System::Windows::Forms::GroupBox());
			this->button_applyData = (gcnew System::Windows::Forms::Button());
			this->label_ampl = (gcnew System::Windows::Forms::Label());
			this->textBox_ampl = (gcnew System::Windows::Forms::TextBox());
			this->textBox_freq = (gcnew System::Windows::Forms::TextBox());
			this->label_freq = (gcnew System::Windows::Forms::Label());
			this->groupBox_control = (gcnew System::Windows::Forms::GroupBox());
			this->button_allGraphVisiblity = (gcnew System::Windows::Forms::Button());
			this->button_start = (gcnew System::Windows::Forms::Button());
			this->button_stop = (gcnew System::Windows::Forms::Button());
			this->chart1 = (gcnew System::Windows::Forms::DataVisualization::Charting::Chart());
			this->timer1 = (gcnew System::Windows::Forms::Timer(this->components));
			this->richTextBox1 = (gcnew System::Windows::Forms::RichTextBox());
			this->menuStrip1->SuspendLayout();
			this->groupBox_data->SuspendLayout();
			this->groupBox_control->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->chart1))->BeginInit();
			this->SuspendLayout();
			// 
			// menuStrip1
			// 
			this->menuStrip1->ImageScalingSize = System::Drawing::Size(20, 20);
			this->menuStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(3) {
				this->файлToolStripMenuItem,
					this->оПрограммеToolStripMenuItem, this->выходToolStripMenuItem
			});
			this->menuStrip1->Location = System::Drawing::Point(0, 0);
			this->menuStrip1->Name = L"menuStrip1";
			this->menuStrip1->Padding = System::Windows::Forms::Padding(5, 2, 0, 2);
			this->menuStrip1->Size = System::Drawing::Size(1776, 28);
			this->menuStrip1->TabIndex = 0;
			this->menuStrip1->Text = L"menuStrip1";
			// 
			// файлToolStripMenuItem
			// 
			this->файлToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {
				this->открытьToolStripMenuItem,
					this->сохранитьToolStripMenuItem
			});
			this->файлToolStripMenuItem->Name = L"файлToolStripMenuItem";
			this->файлToolStripMenuItem->Size = System::Drawing::Size(59, 24);
			this->файлToolStripMenuItem->Text = L"Файл";
			// 
			// открытьToolStripMenuItem
			// 
			this->открытьToolStripMenuItem->Name = L"открытьToolStripMenuItem";
			this->открытьToolStripMenuItem->Size = System::Drawing::Size(205, 26);
			this->открытьToolStripMenuItem->Text = L"Загрузить файл";
			this->открытьToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::открытьToolStripMenuItem_Click);
			// 
			// сохранитьToolStripMenuItem
			// 
			this->сохранитьToolStripMenuItem->Name = L"сохранитьToolStripMenuItem";
			this->сохранитьToolStripMenuItem->Size = System::Drawing::Size(205, 26);
			this->сохранитьToolStripMenuItem->Text = L"Сохранить файл";
			this->сохранитьToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::сохранитьToolStripMenuItem_Click);
			// 
			// оПрограммеToolStripMenuItem
			// 
			this->оПрограммеToolStripMenuItem->Name = L"оПрограммеToolStripMenuItem";
			this->оПрограммеToolStripMenuItem->Size = System::Drawing::Size(118, 24);
			this->оПрограммеToolStripMenuItem->Text = L"О программе";
			this->оПрограммеToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::оПрограммеToolStripMenuItem_Click);
			// 
			// выходToolStripMenuItem
			// 
			this->выходToolStripMenuItem->Name = L"выходToolStripMenuItem";
			this->выходToolStripMenuItem->Size = System::Drawing::Size(67, 24);
			this->выходToolStripMenuItem->Text = L"Выход";
			this->выходToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::выходToolStripMenuItem_Click);
			// 
			// groupBox_data
			// 
			this->groupBox_data->Controls->Add(this->button_applyData);
			this->groupBox_data->Controls->Add(this->label_ampl);
			this->groupBox_data->Controls->Add(this->textBox_ampl);
			this->groupBox_data->Controls->Add(this->textBox_freq);
			this->groupBox_data->Controls->Add(this->label_freq);
			this->groupBox_data->Location = System::Drawing::Point(17, 34);
			this->groupBox_data->Margin = System::Windows::Forms::Padding(4);
			this->groupBox_data->Name = L"groupBox_data";
			this->groupBox_data->Padding = System::Windows::Forms::Padding(4);
			this->groupBox_data->Size = System::Drawing::Size(321, 204);
			this->groupBox_data->TabIndex = 1;
			this->groupBox_data->TabStop = false;
			this->groupBox_data->Text = L"Данные";
			// 
			// button_applyData
			// 
			this->button_applyData->Location = System::Drawing::Point(213, 169);
			this->button_applyData->Margin = System::Windows::Forms::Padding(4);
			this->button_applyData->Name = L"button_applyData";
			this->button_applyData->Size = System::Drawing::Size(100, 28);
			this->button_applyData->TabIndex = 4;
			this->button_applyData->Text = L"Принять";
			this->button_applyData->UseVisualStyleBackColor = true;
			this->button_applyData->Click += gcnew System::EventHandler(this, &MyForm::button_applyData_Click);
			// 
			// label_ampl
			// 
			this->label_ampl->AutoSize = true;
			this->label_ampl->Location = System::Drawing::Point(9, 85);
			this->label_ampl->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label_ampl->Name = L"label_ampl";
			this->label_ampl->Size = System::Drawing::Size(199, 16);
			this->label_ampl->TabIndex = 3;
			this->label_ampl->Text = L"Амплитуда (от 100 до 10000 В)";
			// 
			// textBox_ampl
			// 
			this->textBox_ampl->Location = System::Drawing::Point(8, 105);
			this->textBox_ampl->Margin = System::Windows::Forms::Padding(4);
			this->textBox_ampl->Name = L"textBox_ampl";
			this->textBox_ampl->Size = System::Drawing::Size(236, 22);
			this->textBox_ampl->TabIndex = 2;
			// 
			// textBox_freq
			// 
			this->textBox_freq->Location = System::Drawing::Point(9, 46);
			this->textBox_freq->Margin = System::Windows::Forms::Padding(4);
			this->textBox_freq->Name = L"textBox_freq";
			this->textBox_freq->Size = System::Drawing::Size(235, 22);
			this->textBox_freq->TabIndex = 1;
			// 
			// label_freq
			// 
			this->label_freq->AutoSize = true;
			this->label_freq->Location = System::Drawing::Point(9, 25);
			this->label_freq->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label_freq->Name = L"label_freq";
			this->label_freq->Size = System::Drawing::Size(158, 16);
			this->label_freq->TabIndex = 0;
			this->label_freq->Text = L"Частота (от 1 до 100 Гц)";
			// 
			// groupBox_control
			// 
			this->groupBox_control->Controls->Add(this->button_allGraphVisiblity);
			this->groupBox_control->Controls->Add(this->button_start);
			this->groupBox_control->Controls->Add(this->button_stop);
			this->groupBox_control->Location = System::Drawing::Point(17, 247);
			this->groupBox_control->Margin = System::Windows::Forms::Padding(4);
			this->groupBox_control->Name = L"groupBox_control";
			this->groupBox_control->Padding = System::Windows::Forms::Padding(4);
			this->groupBox_control->Size = System::Drawing::Size(321, 189);
			this->groupBox_control->TabIndex = 2;
			this->groupBox_control->TabStop = false;
			this->groupBox_control->Text = L"Управление";
			// 
			// button_allGraphVisiblity
			// 
			this->button_allGraphVisiblity->Location = System::Drawing::Point(7, 22);
			this->button_allGraphVisiblity->Name = L"button_allGraphVisiblity";
			this->button_allGraphVisiblity->Size = System::Drawing::Size(306, 23);
			this->button_allGraphVisiblity->TabIndex = 2;
			this->button_allGraphVisiblity->Text = L"Показать весь график (старт для сброса)";
			this->button_allGraphVisiblity->UseVisualStyleBackColor = true;
			this->button_allGraphVisiblity->Click += gcnew System::EventHandler(this, &MyForm::button_allGraphVisiblity_Click);
			// 
			// button_start
			// 
			this->button_start->Enabled = false;
			this->button_start->Location = System::Drawing::Point(213, 153);
			this->button_start->Margin = System::Windows::Forms::Padding(4);
			this->button_start->Name = L"button_start";
			this->button_start->Size = System::Drawing::Size(100, 28);
			this->button_start->TabIndex = 1;
			this->button_start->Text = L"Старт";
			this->button_start->UseVisualStyleBackColor = true;
			this->button_start->Click += gcnew System::EventHandler(this, &MyForm::button_start_Click);
			// 
			// button_stop
			// 
			this->button_stop->Enabled = false;
			this->button_stop->Location = System::Drawing::Point(8, 153);
			this->button_stop->Margin = System::Windows::Forms::Padding(4);
			this->button_stop->Name = L"button_stop";
			this->button_stop->Size = System::Drawing::Size(100, 28);
			this->button_stop->TabIndex = 0;
			this->button_stop->Text = L"Стоп";
			this->button_stop->UseVisualStyleBackColor = true;
			this->button_stop->Click += gcnew System::EventHandler(this, &MyForm::button_stop_Click);
			// 
			// chart1
			// 
			chartArea3->AxisX->ScaleView->MinSizeType = System::Windows::Forms::DataVisualization::Charting::DateTimeIntervalType::Milliseconds;
			chartArea3->AxisX->ScaleView->SizeType = System::Windows::Forms::DataVisualization::Charting::DateTimeIntervalType::Milliseconds;
			chartArea3->AxisX->ScaleView->SmallScrollMinSizeType = System::Windows::Forms::DataVisualization::Charting::DateTimeIntervalType::Milliseconds;
			chartArea3->AxisX->Title = L"Время (C)";
			chartArea3->AxisY->Title = L"Амплитуда (В)";
			chartArea3->AxisY->TitleAlignment = System::Drawing::StringAlignment::Far;
			chartArea3->Name = L"ChartArea1";
			this->chart1->ChartAreas->Add(chartArea3);
			legend3->Enabled = false;
			legend3->Name = L"Legend1";
			this->chart1->Legends->Add(legend3);
			this->chart1->Location = System::Drawing::Point(367, 34);
			this->chart1->Margin = System::Windows::Forms::Padding(4);
			this->chart1->Name = L"chart1";
			series3->ChartArea = L"ChartArea1";
			series3->ChartType = System::Windows::Forms::DataVisualization::Charting::SeriesChartType::Spline;
			series3->Legend = L"Legend1";
			series3->Name = L"Sinus";
			this->chart1->Series->Add(series3);
			this->chart1->Size = System::Drawing::Size(1432, 729);
			this->chart1->TabIndex = 3;
			this->chart1->Text = L"chart1";
			this->chart1->MouseWheel += gcnew MouseEventHandler(this, &MyForm::chart1_MouseWheel);
			this->chart1->MouseMove += gcnew MouseEventHandler(this, &MyForm::chart1_MouseMove);
			this->chart1->MouseUp += gcnew MouseEventHandler(this, &MyForm::chart1_MouseUp);
			this->chart1->MouseDown += gcnew MouseEventHandler(this, &MyForm::chart1_MouseDown);
			
			// 
			// timer1
			// 
			this->timer1->Tick += gcnew System::EventHandler(this, &MyForm::timer1_Tick);
			// 
			// richTextBox1
			// 
			this->richTextBox1->Enabled = false;
			this->richTextBox1->Location = System::Drawing::Point(17, 481);
			this->richTextBox1->Name = L"richTextBox1";
			this->richTextBox1->Size = System::Drawing::Size(321, 117);
			this->richTextBox1->TabIndex = 4;
			this->richTextBox1->Text = L"Приближение графика в правой его части вызывает исключение.\nОтловил, но не смог р"
				L"азобраться что с ним сделать.\nПеретаскивание области графика мышью работает корр"
				L"ектно.";
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1776, 778);
			this->Controls->Add(this->richTextBox1);
			this->Controls->Add(this->chart1);
			this->Controls->Add(this->groupBox_control);
			this->Controls->Add(this->groupBox_data);
			this->Controls->Add(this->menuStrip1);
			this->MainMenuStrip = this->menuStrip1;
			this->Margin = System::Windows::Forms::Padding(4);
			this->Name = L"MyForm";
			this->Text = L"MyForm";
			this->menuStrip1->ResumeLayout(false);
			this->menuStrip1->PerformLayout();
			this->groupBox_data->ResumeLayout(false);
			this->groupBox_data->PerformLayout();
			this->groupBox_control->ResumeLayout(false);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->chart1))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

	//Переменные и данные
	private: double freq, ampl, step;				//Частота, амплитуда и шаг отрисовки графика, для реализации графика
	private: double x = 0, y;						//Точка x - начальная координата для расчётов		
	private: bool isLeftButtonPressed = false;
	private: Point mouseDown = Point::Empty;

	//Основной контейнер для хранения координат
	private:
	Generic::List<PointF>^ list = gcnew Generic::List<PointF>();
	
	//Метод хранящий параметры графика по умолчанию (если пользователь ничего не ввёл)
	private: void DefaultParams();	
	
	//События взаимодействия пользователя с мышью
	System::Void chart1_MouseWheel(System::Object^ sender, MouseEventArgs^ e);
	System::Void chart1_MouseMove(System::Object^ sender, MouseEventArgs^ e);
	System::Void chart1_MouseUp(System::Object^ sender, MouseEventArgs^ e);
	System::Void chart1_MouseDown(System::Object^ sender, MouseEventArgs^ e);


	//кнопки в подменю Файл
	private: System::Void открытьToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e);
	private: System::Void сохранитьToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e);

	//О программе
	private: System::Void оПрограммеToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e);

	//Выход
	private: System::Void выходToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e);

	//Принять данные
	private: System::Void button_applyData_Click(System::Object^ sender, System::EventArgs^ e);

	//Кнопки управления (старт, стоп, показать график)
	private: System::Void button_start_Click(System::Object^ sender, System::EventArgs^ e);
	private: System::Void button_stop_Click(System::Object^ sender, System::EventArgs^ e);
	private: System::Void button_allGraphVisiblity_Click(System::Object^ sender, System::EventArgs^ e);

	//Событие тика таймера
	private: System::Void timer1_Tick(System::Object^ sender, System::EventArgs^ e);

};
} 
