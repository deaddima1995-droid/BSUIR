#pragma once
#include <string>

namespace Task5 {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	struct node {
		char data;
		node* next;
	};

	struct stack {
		node* top;

		stack() {
			top = nullptr;
		}

		void push(char x) {
			node *temp = new node;
			temp->data = x;
			temp->next = top;
			top = temp;
		}

		char pop() {
			char result = top->data;
			node* temp = top->next;
			delete top;
			top = temp;
			return result;
		}

		char peek() {
			return top->data;
		}

		bool isEmpty() {
			return top == nullptr;
		}
	};
	int prior(char);


	int prior(char symbol) {
		switch (symbol) {
			case '*': case'/': return 3;
			case '-': case'+': return 2;
			case '(': return 1;
			default: return 0;
		}
	}



	/// <summary>
	/// Сводка для Task_OPZ
	/// </summary>
	public ref class Task_OPZ : public System::Windows::Forms::Form
	{
	public:
		
		Task_OPZ(void)
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
		~Task_OPZ()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::DataGridView^ dataGridView1;
	protected:
	private: System::Windows::Forms::Button^ button1;
	private: System::Windows::Forms::Button^ button2;
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::Label^ label2;
	private: System::Windows::Forms::Label^ label3;
	private: System::Windows::Forms::TextBox^ textBox1;
	private: System::Windows::Forms::TextBox^ textBox2;
	private: System::Windows::Forms::TextBox^ textBox3;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^ Column1;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^ Column2;







	private:
		/// <summary>
		/// Обязательная переменная конструктора.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Требуемый метод для поддержки конструктора — не изменяйте 
		/// содержимое этого метода с помощью редактора кода.
		/// </summary>
		void InitializeComponent(void)
		{
			System::Windows::Forms::DataGridViewCellStyle^ dataGridViewCellStyle1 = (gcnew System::Windows::Forms::DataGridViewCellStyle());
			this->dataGridView1 = (gcnew System::Windows::Forms::DataGridView());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->textBox2 = (gcnew System::Windows::Forms::TextBox());
			this->textBox3 = (gcnew System::Windows::Forms::TextBox());
			this->Column1 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->Column2 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridView1))->BeginInit();
			this->SuspendLayout();
			// 
			// dataGridView1
			// 
			this->dataGridView1->AutoSizeColumnsMode = System::Windows::Forms::DataGridViewAutoSizeColumnsMode::Fill;
			this->dataGridView1->AutoSizeRowsMode = System::Windows::Forms::DataGridViewAutoSizeRowsMode::AllCells;
			this->dataGridView1->BackgroundColor = System::Drawing::Color::White;
			this->dataGridView1->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			this->dataGridView1->Columns->AddRange(gcnew cli::array< System::Windows::Forms::DataGridViewColumn^  >(2) {
				this->Column1,
					this->Column2
			});
			this->dataGridView1->Location = System::Drawing::Point(12, 12);
			this->dataGridView1->Name = L"dataGridView1";
			this->dataGridView1->RowHeadersVisible = false;
			this->dataGridView1->ScrollBars = System::Windows::Forms::ScrollBars::Vertical;
			this->dataGridView1->Size = System::Drawing::Size(239, 186);
			this->dataGridView1->TabIndex = 0;
			// 
			// button1
			// 
			this->button1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->button1->Location = System::Drawing::Point(486, 27);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(107, 51);
			this->button1->TabIndex = 1;
			this->button1->Text = L"Перевести";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &Task_OPZ::button1_Click);
			// 
			// button2
			// 
			this->button2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->button2->Location = System::Drawing::Point(486, 97);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(107, 52);
			this->button2->TabIndex = 2;
			this->button2->Text = L"Посчитать";
			this->button2->UseVisualStyleBackColor = true;
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label1->Location = System::Drawing::Point(278, 14);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(196, 24);
			this->label1->TabIndex = 3;
			this->label1->Text = L"Введите выражение";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label2->Location = System::Drawing::Point(278, 85);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(162, 24);
			this->label2->TabIndex = 4;
			this->label2->Text = L"Полученная ОПЗ";
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label3->Location = System::Drawing::Point(278, 172);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(108, 24);
			this->label3->TabIndex = 5;
			this->label3->Text = L"Результат:";
			// 
			// textBox1
			// 
			this->textBox1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->textBox1->Location = System::Drawing::Point(267, 41);
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(213, 29);
			this->textBox1->TabIndex = 6;
			// 
			// textBox2
			// 
			this->textBox2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->textBox2->Location = System::Drawing::Point(267, 112);
			this->textBox2->Name = L"textBox2";
			this->textBox2->Size = System::Drawing::Size(213, 29);
			this->textBox2->TabIndex = 7;
			// 
			// textBox3
			// 
			this->textBox3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->textBox3->Location = System::Drawing::Point(396, 169);
			this->textBox3->Name = L"textBox3";
			this->textBox3->Size = System::Drawing::Size(100, 29);
			this->textBox3->TabIndex = 8;
			// 
			// Column1
			// 
			dataGridViewCellStyle1->BackColor = System::Drawing::Color::Silver;
			this->Column1->DefaultCellStyle = dataGridViewCellStyle1;
			this->Column1->FillWeight = 50;
			this->Column1->HeaderText = L"Имя";
			this->Column1->MaxInputLength = 1;
			this->Column1->Name = L"Column1";
			this->Column1->ReadOnly = true;
			this->Column1->Resizable = System::Windows::Forms::DataGridViewTriState::False;
			this->Column1->SortMode = System::Windows::Forms::DataGridViewColumnSortMode::NotSortable;
			// 
			// Column2
			// 
			this->Column2->HeaderText = L"Значение";
			this->Column2->Name = L"Column2";
			this->Column2->Resizable = System::Windows::Forms::DataGridViewTriState::False;
			// 
			// Task_OPZ
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->AutoScroll = true;
			this->AutoSize = true;
			this->ClientSize = System::Drawing::Size(608, 213);
			this->Controls->Add(this->textBox3);
			this->Controls->Add(this->textBox2);
			this->Controls->Add(this->textBox1);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->button2);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->dataGridView1);
			this->Name = L"Task_OPZ";
			this->Text = L"Польская запись";
			this->Load += gcnew System::EventHandler(this, &Task_OPZ::Task_OPZ_Load);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridView1))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void button1_Click(System::Object^ sender, System::EventArgs^ e) {
		stack p_stack;
		Char symbol, temp;
		String^ in = textBox1->Text;
		String^ out = "";
		int length = in->Length;
		for (int i = 0; i < length; ++i) {
			symbol = in[i];
			if (symbol >= 'a' && symbol <= 'z') out += symbol;
			if (symbol == '(') p_stack.push(symbol);
			if (symbol == ')') {
				while (p_stack.peek() != '(') {
					temp = p_stack.pop();
					out += temp;
				}
				temp = p_stack.pop();
				
			}
			if (symbol == '*' || symbol == '/' || symbol == '+' || symbol == '-' || symbol == '^') {
				while(!p_stack.isEmpty() && 
					prior(p_stack.peek()) >= prior(symbol)) {
					temp = p_stack.pop();
					out += temp;
				}
				p_stack.push(symbol);
			}
		}
		while (!p_stack.isEmpty()) {
			temp = p_stack.pop();
			out += temp;
		}
		textBox2->Text = out;
	}
private: System::Void Task_OPZ_Load(System::Object^ sender, System::EventArgs^ e) {
	textBox1->Text = "a/(b+c-d*e)";
	textBox2->Text = "";
	char a = 'a';
	String^ data = "abcde";
	for (int i = 0; i < data->Length; i++) {
		dataGridView1->Rows->Add();
		dataGridView1->Rows[i]->Cells[0]->Value = data[i];
		a++;
	}
	dataGridView1->Rows[0]->Cells[1]->Value = 7.6;
	dataGridView1->Rows[1]->Cells[1]->Value = 4.8;
	dataGridView1->Rows[2]->Cells[1]->Value = 3.5;
	dataGridView1->Rows[3]->Cells[1]->Value = 9.1;
	dataGridView1->Rows[4]->Cells[1]->Value = 0.2;
}
};
}
