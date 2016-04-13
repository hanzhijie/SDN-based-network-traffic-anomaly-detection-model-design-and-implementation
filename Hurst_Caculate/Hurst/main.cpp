
#include <fstream>
#include <iostream>
#include <math.h>
#include <time.h>
#include <vector>
#include <stdlib.h>

using namespace std;

class Plot {
	public:
		double x;
		double y;
};
vector<Plot> graph;

int main() {
	double datapoint;
	vector<double> data;
	vector<double>::iterator it1;
	vector<double>::iterator it2;
	vector<double> array1;
	vector<double> array2;
	double Mean;
	int NoOfDataPoints;
	int NoOfPlottedPoints;
	int PlottedPointNo;
	int NoOfPeriods;
	int PeriodNo;
	int n;
	int i,j;
	int m;
	const double logten = log((double)10);
	double R, totalR;
	double S, totalS;
	double RS;
	double Summ, SumSquared;
	double Maxi, Mini;
	double Sumx, Sumy, Sumxy, Sumxx,Sumyy;
	double H;
	clock_t init, final;
	if (true) {


	//使用前需要在D盘根目录下新建空packetData.txt文件
	ifstream inputfile("aa.txt");
			if (!inputfile) {
			cout << "Failed to open input file." << endl;
			return -1;
		}
		while (inputfile >> datapoint)
			data.push_back(datapoint);

	//获取所有数据的点
		NoOfDataPoints = data.size();
		if (NoOfDataPoints > 3) {
			init=clock();
			ofstream outputfile("bb.txt");
			if (!outputfile) {
				cout << "Failed to open output file." << endl;

				return -1;
			}
  			outputfile << "Number of data points: " << NoOfDataPoints << endl;
			NoOfPlottedPoints = NoOfDataPoints - 2;
			graph.resize(NoOfPlottedPoints);  //图像打小变换原形


			//开始主循环
			for (n = 3; n <= NoOfDataPoints; n++) {
				totalR = 0;
				totalS = 0;
				NoOfPeriods = NoOfDataPoints - n + 1;
				for (PeriodNo = 0; PeriodNo < NoOfPeriods; PeriodNo++) {
					//cout << ".";
					array1.clear();
					array2.clear();
					for (i = 0; i<n; i++)
						array1.push_back(data[PeriodNo + i]);//stl 容器中的函数，用于在后面添加一项
					for (i = 0; i<n; i++)
						array2.push_back(0);
					Summ = 0;
					SumSquared = 0;
					for(it1=array1.begin(); it1!=array1.end(); it1++) {
						Summ = Summ + *it1;
						SumSquared = SumSquared + (*it1) * (*it1);
					}
					Mean = Summ / n;
					//S = sqrt((SumSquared - (Summ * Summ) / n) / (n - 1));
					//S = sqrt((SumSquared - (Summ * Summ) / n) / n);
					S = sqrt((SumSquared - 2*Summ*Mean+n*Mean*Mean) / n );

					for(it1=array1.begin(); it1!=array1.end(); ++it1)
						*it1 = *it1 - Mean;
					for(int i2=0; i2 < n; ++i2)
						for(int i1=0; i1 < i2; ++i1)
							array2[i2] = array2[i2] + array1[i1];
					Maxi = array2[0];
					Mini = array2[0];
					for(it2=array2.begin(); it2!=array2.end(); ++it2) {
						if (*it2 > Maxi)
							Maxi = *it2;
						if (*it2 < Mini)
							Mini = *it2;
					}
					R = Maxi - Mini;
					totalR = totalR + R;
					totalS = totalS + S;
				}
				cout << endl;
				R = totalR / NoOfPeriods;
				S = totalS / NoOfPeriods;
				RS = R / S;
				PlottedPointNo = n - 3;
				graph[PlottedPointNo].x = (log((double)n)) / logten;
				graph[PlottedPointNo].y = (log((double)RS)) / logten;
			}
			Sumx = 0;
			Sumy = 0;
			Sumxy = 0;
			Sumxx = 0;
			Sumyy=0;
			for (i = 0; i < NoOfPlottedPoints; i++) {
				Sumx = Sumx + graph[i].x;
				Sumy = Sumy + graph[i].y;
				Sumxy = Sumxy + (graph[i].x) * (graph[i].y);
				Sumxx = Sumxx + (graph[i].x) * (graph[i].x);
				Sumyy = Sumyy+(graph[i].y) * (graph[i].y);

			}
			outputfile << endl;
			outputfile << "Log(n) Log(R/S)" << endl;
			for (i = 0; i < NoOfPlottedPoints; i++)
				outputfile << graph[i].x << " " << graph[i].y << endl;

			//计算Hurst系数
		    H = (Sumxy - ((Sumx * Sumy) / NoOfPlottedPoints)) / (Sumxx - ((Sumx * Sumx) / NoOfPlottedPoints));
			//H = (Sumxy - ((Sumx * Sumy) / NoOfPlottedPoints)) / sqrt(Sumxx - ((Sumx * Sumx) / NoOfPlottedPoints))*(Sumyy-((Sumy*Sumy)/NoOfPlottedPoints));

			outputfile << endl;
			cout << "H = " << H << endl;
			outputfile << "H = " << H << endl;
			final=clock()-init;
			cout << "Time taken: " << (double)final / ((double)CLOCKS_PER_SEC) << " seconds" << endl;
			outputfile << endl;
			outputfile << "Time taken: " << (double)final / ((double)CLOCKS_PER_SEC) << " seconds" << endl;
			outputfile.close();

		}
		else {
			cout << "Number of data points: " << NoOfDataPoints << endl;
			cout << "The calculation requires at least 4 data points." << endl;
		}
		inputfile.close();
	}
	else
		cout << "Usage: hurst inputfilename (outputfilename)" << endl;

}
