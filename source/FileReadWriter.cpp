#include "FileReadWriter.h"


void CourseWriter(course& c, std::u32string filepath) {
	TextWriter tw{ filepath };
	if (not tw)return;
	tw.writeln(U"Fukusosuuheimengame map v2");

	tw.writeln(c.cmds.size());
	for (int i = 0; i < c.cmds.size(); i++) {
		tw.writeln((int)c.cmds[i].cmdtype);
		tw.writeln((int)c.cmds[i].value1);
		tw.writeln((int)c.cmds[i].nokori);
	}

	tw.writeln(c.pobjs.size());
	for (auto& e : c.pobjs) {
		tw.writeln((int)e.type);
		tw.writeln(e.p1.real());
		tw.writeln(e.p1.imag());
		tw.writeln(e.p2.real());
		tw.writeln(e.p2.imag());
		tw.writeln(e.value1);
	}

	tw.writeln(c.startpoint.text);
	tw.writeln(c.startpoint.textoffset);
	tw.writeln(c.startpoint.at.real());
	tw.writeln(c.startpoint.at.imag());

	tw.writeln(c.goalpoint.text);
	tw.writeln(c.goalpoint.textoffset);
	tw.writeln(c.goalpoint.at.real());
	tw.writeln(c.goalpoint.at.imag());
}

void CourseLoader(course& c, FilePath fp) {

	int ver = 0;
	{
		TextReader tr{ fp };
		if (not tr) {
			c.checkdpointnum = INT_MAX;
			return;
		}

		{
			String tmpline = tr.readLine().value();
			if (tmpline == U"Fukusosuuheimengame map") {
				ver = 1;
			}
			else if (tmpline == U"Fukusosuuheimengame map v2") {
				ver = 2;
			}

			else return;
		}
		String tl;
		String tl2;
		tr.readLine(tl);
		int cmdsize = Parse<int>(tl);
		c.cmds = std::vector<cmd>(cmdsize);
		for (int i = 0; i < cmdsize; i++) {
			tr.readLine(tl);
			c.cmds[i].cmdtype = (cmd::type)Parse<int>(tl);
			tr.readLine(tl);
			c.cmds[i].value1 = Parse<int>(tl);
			if (ver == 2) {
				tr.readLine(tl);
				c.cmds[i].nokori = Parse<int>(tl);
			}
		}

		tr.readLine(tl);
		int opbjsize = Parse<int>(tl);
		c.pobjs = std::vector<pointobject>(opbjsize);
		for (int i = 0; i < opbjsize; i++) {
			tr.readLine(tl);
			c.pobjs[i].type = (pointobject::objtype)Parse<int>(tl);
			tr.readLine(tl); tr.readLine(tl2);
			c.pobjs[i].p1 = complex(Parse<int>(tl), Parse<int>(tl2));
			tr.readLine(tl); tr.readLine(tl2);
			c.pobjs[i].p2 = complex(Parse<int>(tl), Parse<int>(tl2));
			tr.readLine(tl);
			c.pobjs[i].value1 = Parse<int>(tl);
		}
		tr.readLine(tl);
		c.startpoint.text = tl;
		tr.readLine(tl);
		c.startpoint.textoffset = Parse<Point>(tl);
		tr.readLine(tl); tr.readLine(tl2);
		c.startpoint.at = complex(Parse<int>(tl), Parse<int>(tl2));

		tr.readLine(tl);
		c.goalpoint.text = tl;
		tr.readLine(tl);
		c.goalpoint.textoffset = Parse<Point>(tl);
		tr.readLine(tl); tr.readLine(tl2);
		c.goalpoint.at = complex(Parse<int>(tl), Parse<int>(tl2));

		c.checkdpointnum = 0;
		for (auto e : c.pobjs) {
			if (e.type == pointobject::objtype::checkpoint) {
				c.allcheckpointnum++;
			}
		}
	}
	if (ver == 1) {
		CourseWriter(c, fp.toUTF32());
		CourseLoader(c, fp);
	}
	return;
}


