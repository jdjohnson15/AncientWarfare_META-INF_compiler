#include "boost/filesystem.hpp"
#include <iostream>

using namespace boost::filesystem;
using namespace std;

void writeMeta(boost::filesystem::ofstream* file, path name);

void writeMetaSub(boost::filesystem::ofstream* file, path name, string group);

vector<path> getImagePaths(path p);

string fixSlashes(string s);

string groups[14] = {
	".\/bandit",
	".\/pirate",
	".\/viking",
	".\/desert",
	".\/native",
	".\/custom1",
	".\/custom2",
	".\/custom3",
	".\/combat",
	".\/priest",
	".\/courier",
	".\/trader",
	".\/bard",
	".\/worker" };

int main()
{
	for (int i = 0; i < 14; i++) {
		path tp(groups[i]);
		//if (!exists(tp))
			//create_directory(tp);	
	}
	boost::filesystem::ofstream file("skin-pack.meta");
	
	//get all subdirectories in folder
	path p(".");

	directory_iterator end_itr;
	vector<path> folders;

	// cycle through the directory
	for (directory_iterator itr(p); itr != end_itr; ++itr)
	{
		// If it's a directory, save it in a list to use for making name groups
		if (!is_regular_file(itr->path())) {
			// assign current file name to current_file and echo it out to the console.
			folders.push_back(itr->path());
		}
		//if it's a png file, configure it in the meta file without a group. It will be referenced as-is
		else {
			if (itr->path().string().compare(itr->path().string().size() - 3, 3, "png") == 0) {
				string n = "";
				string p = "";
				n.append(itr->path().string(), 2, itr->path().string().size() - 6);
				p.append(itr->path().string(), 2, itr->path().string().size() - 2);
				cout << n << "=" << p << endl;
				file << n << "=" << p << endl;
			}
		}
	}

	for (int i = 0; i < folders.size(); ++i) {
		writeMeta(&file, folders.at(i));
	}

	/*
	
	
	each non-player group should have at least one of the following
	archer
	archer_elite
	cavalry
	female
	leader
	leader_elite
	male
	mounted_archer
	priest
	soldier
	soldier-elite
	trader

	player-controlled npcs should have the following:
	archer
	bard
	combat
	commander
	courier
	engineer
	medic
	priest
	soldier
	trader
	worker
	craftsman
	farmer
	lumberjack
	miner
	researcher

	*/



	file.close();
	
	system("pause");
}

void writeMeta(boost::filesystem::ofstream* file, path name) {
	
	string dir_name = "";
	dir_name.append(name.string(), 2, name.string().size() - 2);

	directory_iterator end_itr;
	//follow more strict conventions if directory name falls under one of the pre-defined faction names
	if (dir_name.compare("bandit") == 0 ||
		dir_name.compare("pirate") == 0 ||
		dir_name.compare("viking") == 0 ||
		dir_name.compare("desert")  == 0 ||
		dir_name.compare("native")  == 0 ||
		dir_name.compare("custom1") == 0 ||
		dir_name.compare("custom2") == 0 ||
		dir_name.compare("custom3") == 0 ||
		dir_name.compare("combat") == 0 ||
		dir_name.compare("priest") == 0 ||
		dir_name.compare("courier") == 0 ||
		dir_name.compare("trader") == 0 ||
		dir_name.compare("bard") == 0 ||
		dir_name.compare("worker") == 0 ){
		writeMetaSub(file, name, dir_name);
	}
	//for custom texture groups
	else {
		string group = "";
		group.append(name.string(), 2, name.string().size()-2);
		vector<path> imgPaths = getImagePaths(name);
		for (int i = 0; i < imgPaths.size(); i++) {
			string img = "";
			img.append(imgPaths.at(i).string(), 2, imgPaths.at(i).string().size() - 2);
			cout << group << "=" << img << endl;
			*file << group << "=" << fixSlashes(img) << endl;
		}
		for (directory_iterator itr(name); itr != end_itr; ++itr)
		{/*
			string img = "";
			img.append(itr->path().string(), 2, itr->path().string().size() - 2);
			cout << group << "=" << img << endl;
			*file << group << "=" << fixSlashes(img) << endl;*/
		}
	}
}

void writeMetaSub(boost::filesystem::ofstream* file, path name, string group) {
	directory_iterator end_itr;
	vector<path> folders;
	for (directory_iterator itr(name); itr != end_itr; ++itr)
	{
		folders.push_back(itr->path());
	}
	for (int i = 0; i < folders.size(); ++i) {
		directory_iterator end_itr2;
		if (is_directory(folders.at(i))) {
			for (directory_iterator itr(folders.at(i)); itr != end_itr2; ++itr)
			{
				string classname = "";
				classname.append(itr->path().string(), 3 + group.size(), itr->path().string().size() - group.size() - itr->path().filename().string().size() - 4);
				if (itr->path().string().compare(itr->path().string().size() - 3, 3, "png") == 0) {
						string img = "";
						img.append(itr->path().string(), 2, itr->path().string().size() - 2);
						cout << group << "." << classname << "=" << img << endl;
						*file << group << "." << classname << "=" << fixSlashes(img) << endl;
				}

			}
		}
		else {
			string img = "";
			img.append(folders.at(i).string(), 2, folders.at(i).string().size() - 2);
			if (group.compare("worker") || group.compare("trader") || group.compare("bard") || group.compare("priest") || group.compare("courier")) {
				cout << group << "=" << img << endl;
				*file << group << "=" << fixSlashes(img) << endl;
			}
			else {
				int r = rand() % 2;
				if (r == 0) {
					cout << group << ".civilian.male" << "=" << img << endl;
					*file << group << ".civilian.male" << "=" << fixSlashes(img) << endl;
				}

				else {
					cout << group << ".civilian.female" << "=" << img << endl;
					*file << group << ".civilian.female" << "=" << fixSlashes(img) << endl;
				}
			}
			
		}
	}
	//populate file with naming for role groups
	/*
	if (dir_name.compare("archer")) {
		group.append(name.string(), 2, name.string().size() - 9);
		
	}
	else if (dir_name.compare("archer_elite")) {

	}
	else if (dir_name.compare("cavalry")) {

	}
	else if (dir_name.compare("female")) {

	}
	else if (dir_name.compare("leader")) {

	}
	else if (dir_name.compare("leader_elite")) {

	}
	else if (dir_name.compare("male")) {

	}
	else if (dir_name.compare("mounted_archer")) {

	}
	else if (dir_name.compare("soldier-elite")) {

	}
	else if (dir_name.compare("soldier")) {

	}
	else if (dir_name.compare("trader")) {

	}
	*/
}

vector<path> getImagePaths(path p) {
	vector<path> folders, files;
	directory_iterator end_itr;
	for (directory_iterator itr(p); itr != end_itr; ++itr)
	{
		if (is_directory(itr->path()))
			folders.push_back(itr->path());
		else
			files.push_back(itr->path());
	}
	for (int i = 0; i < folders.size(); i++) {
		vector<path> temp = getImagePaths(folders.at(i));
		files.insert(files.end(), temp.begin(), temp.end());
	}
	return files;
}

string fixSlashes(string s)
{
	string o = "";
	for (int i = 0; i < s.size(); ++i) {
		if (s[i] == '\\')
			o.append("/");
		else
			o.append(s,i,1);
	}
	return o;
}
