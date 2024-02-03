#include<iostream>
#include<iomanip>
#include <cpprest/http_client.h>
#include<cpprest/filestream.h>
#include<string>

using namespace std;
using namespace web;
using namespace web::http;
using namespace web::http::client;



double kelvin(double &temperature );
void style();
void style2();

int main() {

	string city;
	double temp, humidity, pressure;
	string weather;
	cout << "\n";
	cout  << left << setw(23) << setfill('-') << "-" << "Weather app " << right << setw(23) << setfill('-') << '-' << endl;
	style();
	cout << "Enter the city name : ";
	getline(cin, city);
	http_client client(U("https://api.openweathermap.org/data/2.5"));
	uri_builder builder(U("/weather","wind"));
	builder.append_query(U("q"), utility::conversions::to_string_t(city));
	builder.append_query(U("appid"), U("105245613c8acdf0331789027b600ee9"));
	http_request request(methods::GET);
	request.set_request_uri(builder.to_string());


	client.request(request).then([&,temp,humidity,pressure,weather](http_response response) {

		return response.extract_json();





		}
	).then([&temp , &humidity ,&weather,&pressure](web::json::value body) {
			temp = body[U("main")][U("temp")].as_double();
			pressure = body[U("main")][U("pressure")].as_double();
			humidity= body[U("main")][U("humidity")].as_double();
			weather = utility::conversions::to_utf8string(body[U("weather")][0][U("main")].as_string());




		} 
		).wait();

		cout << "\n";
		style2();
		cout<<"Temperature : " <<kelvin(temp) <<" C" << endl;
		style2();
		cout <<"Humidity  : " << humidity <<" % " << endl;
		style2();
		cout <<"Wheather : " << weather << endl;
		style2();
		cout <<"Pressure : " << pressure << endl;

		return 0;


}
// function for convert the celsisus 
double kelvin(double& temperature) {
	 
	


	return temperature - 273.15 ;
}
// function to style 
void style() {
	cout <<"\n" << setw(100) << setfill('-') << "\n" << endl;
}

void style2() {

	cout << setw(10) << setfill(' ')<<" ";
}