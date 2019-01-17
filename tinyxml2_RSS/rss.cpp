#include "rss.h"

regex reg1("<.{1,8}>");
regex reg2("<.{9,200}>");
string white("");
string str("");

//读txt文档获取xml文件名
RssReader::RssReader(const char * filename)
{
	ifstream ifs;
	ifs.open(filename);
	string buff;
	_file_number = 0;
	while(ifs >> buff)
	{
		_fileList.push_back(buff);
		_file_number++;
	}
	return;
}

void RssReader::parseRss()
{
	for(int i = 0; i < _file_number; i++)
	{
		XMLDocument doc;
		doc.LoadFile(_fileList[i].c_str());

		cout << doc.Error() << endl;
		if(0 != doc.Error())
		{
			cout << "[ERROR]:load file" << endl;
			cout << ": " << _fileList[i].c_str() << endl;
			return;
		}

		XMLElement* root = doc.RootElement();
		if(nullptr == root)
		{
			cout << "[ERROR]: root failed!" << endl;
			cout << ": " << _fileList[i].c_str() << endl;
			continue;
		}
		XMLElement* channel = root->FirstChildElement("channel");
		if(nullptr == channel)
		{
			cout << "[ERROR]:get fiest channel element" << endl;
			cout << ": " << _fileList[i].c_str() << endl;
			continue;
		}
		cout << "Filename: " << _fileList[i].c_str() << endl;
		XMLElement* title = channel->FirstChildElement("title");
		cout << title->Name() 
			 << " : "
		 << title->GetText() 
		 << endl;

		XMLElement* item = title->NextSiblingElement();

		while(item)
		{
			if(strcmp( item->Name(), "item") == 0)
				break;
			else
				item = item->NextSiblingElement();
		}

		while(item)
		{
			RssItem tmp;
			//cout << "success in item" << endl;
			XMLElement * item_child = item->FirstChildElement();
			while(item_child)
			{
				if(nullptr == item_child->GetText())
				{
					item_child = item_child->NextSiblingElement();
					continue;
				}
				if(strcmp(item_child->Name(), "title" ) == 0)
				{
					tmp.title.clear();
					str = item_child->GetText();
					str = regex_replace(str, reg1, white);
					str = regex_replace(str, reg2, white);
					tmp.title.append(str);
				}
				else if(strcmp(item_child->Name(), "link") == 0)
				{
					tmp.link.clear();
					str = item_child->GetText();
					str = regex_replace(str, reg1, white);
					str = regex_replace(str, reg2, white);
					tmp.link.append(str);
				}
				else if(strcmp(item_child->Name(), "description") == 0)
				{
					tmp.description.clear();
					str = item_child->GetText();
					str = regex_replace(str, reg1, white);
					str = regex_replace(str, reg2, white);
					tmp.description.append(str);
				}
				else if(strncmp(item_child->Name(), "content", 7) == 0)
				{
					tmp.content.clear();
					str = item_child->GetText();
					str = regex_replace(str, reg1, white);
					str = regex_replace(str, reg2, white);
					tmp.content.append(str);
				}
				item_child = item_child->NextSiblingElement();
			}

			_rss.push_back(tmp);
			item = item->NextSiblingElement();
		}
	}

}

void RssReader::dump(const string & filename)//输出到文件
{
	ofstream _ostream(filename.c_str(), ios::app);
	vector <RssItem>::iterator _begin = _rss.begin();
	vector <RssItem>::iterator _end = _rss.end();

	while(_begin!=_end)
	{
		_ostream << "<doc>" << endl;
		_ostream << "<title>" << _begin->title << "</title>" << endl;
		_ostream << "<link>" << _begin->link << "</link>" << endl;
		_ostream << "<description>" << _begin->description << "</description>" << endl;
		_ostream << "<content>" << _begin->content << "</content>" << endl;
		_ostream << "</doc>" << endl;
		++_begin;
	}
}

