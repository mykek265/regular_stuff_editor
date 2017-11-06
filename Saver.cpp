#include "Saver.h"
#include "CoolScrollBar.h"
std::string					Saver::_name("");
sf::RenderWindow*			Saver::_window(nullptr);
sf::Vector2f*				Saver::_mouse(nullptr);
sf::View*					Saver::_view(nullptr);
sf::RectangleShape			Saver::_fon;
sf::Text					Saver::_tx_name;
sf::Text					Saver::_str;
int							Saver::_state(0);
std::vector<PrimitivBluePr>*Saver::_blpr;
std::vector<JointBluePr>*	Saver::_jblpr;

Saver::Saver()
{
}
Saver::Saver(sf::RenderWindow& window, sf::View& view, sf::Vector2f& mouse, sf::Text& str, std::vector<PrimitivBluePr>& blpr, CoolJointManager& coolJm)
{
	_window = &window;
	_view = &view;
	_mouse	= &mouse;
	_fon.setFillColor(sf::Color::Black);
	_fon.setOutlineColor(sf::Color::White);
	_fon.setOutlineThickness(4);
	_fon.setSize({ WIDTH * 0.5f, HEIGHT * 0.5f });
	_fon.setOrigin(_fon.getSize() * 0.5f);
	_fon.setPosition(view.getCenter());
	_tx_name = str;
	_tx_name.setColor(sf::Color::White);
	_str = _tx_name;
	_blpr = &blpr;
	_jblpr = &(coolJm.joint);
}
void Saver::draw()
{
	_fon.setPosition(_view->getCenter());
	_window->draw(_fon);
	setLiteButton("Ok", _window->getView().getCenter(), _fon.getOrigin(), -0.45f, 0.45f, *_mouse, _state, 1);
	_window->draw(_str);
	setLiteButton("Cancel", _window->getView().getCenter(), _fon.getOrigin(), 0.25f, 0.45f, *_mouse, _state, 2);
	_window->draw(_str);
	setLiteString("Enter the name:\n", _window->getView().getCenter(), _fon.getOrigin(), -0.45f, -0.45f, _str);
	_window->draw(_str);
	setLiteString(_name, _window->getView().getCenter(), _fon.getOrigin(), -0.45f, -0.2f, _tx_name);
	_window->draw(_tx_name);
}
void Saver::enterName(const std::string& str)
{
	_name = str;
	//_tx_name.setString(_name);
}
int findSprByTexture(std::vector<sf::Texture>& t, sf::Sprite* s)
{
	for (int i = 0, N = t.size(); i < N; i++)
	{
		if (&(t[i]) == s->getTexture())
			return i + 1;
	}
	return 0;
}
void Saver::saveBlPr(std::ofstream& fout, PrimitivBluePr& blpr)
{
	std::vector<sf::RectangleShape>& rect = blpr.getRects();
	std::vector<sf::CircleShape>&	 circle = blpr.getCircles();
	std::vector<sf::ConvexShape>&	 triang = blpr.getTriangles();
	std::vector<SensorBpr>*			 sensor = blpr.getSensor();
	std::vector<sf::Sprite>*		 sprite = blpr.getImages();
	std::vector<sf::Texture>*		 texture = CoolScrollBar::getTexturesStatic();
	int kind = 3;
	if (rect.size() == 1 && circle.size() == 0 && triang.size() == 0) kind = 0;
	if (rect.size() == 0 && circle.size() == 1 && triang.size() == 0) kind = 1;
	if (rect.size() == 0 && circle.size() == 0 && triang.size() == 1) kind = 2;
	fout << blpr.getType() << ' ' << sensor->size() << ' ' << blpr.getMyBits() << ' ' << blpr.getColideBits() << std::endl;
	fout << blpr.getDensity() << ' ' << blpr.getFriction() << ' ' << blpr.getElasticity() << ' ' << kind << std::endl;
	if (kind == 0)
	{
		sf::Vector2f sv2(rect[0].getSize()*0.5f), pos(blpr.getPosition() + rect[0].getPosition() + sv2);
		fout << pos.x << ' ' << pos.y << ' ' << sv2.x << ' ' << sv2.y << std::endl;
	}
	if (kind == 1)
	{
		sf::Vector2f pos(blpr.getPosition() + circle[0].getPosition());
		fout << pos.x << ' ' << pos.y << ' ' << circle.begin()->getRotation() << std::endl;
	}
	if (kind == 2)
	{
		sf::Vector2f pos(blpr.getPosition() + triang[0].getPosition() - triang[0].getOrigin());
		fout << pos.x << ' ' << pos.y << ' ';
		fout << triang.begin()->getPoint(0).x << ' ' << triang.begin()->getPoint(0).y << ' ';
		fout << triang.begin()->getPoint(1).x << ' ' << triang.begin()->getPoint(1).y << ' ';
		fout << triang.begin()->getPoint(2).x << ' ' << triang.begin()->getPoint(2).y << std::endl;
	}
	if (kind == 3)
	{
		fout << blpr.getCenter().x << ' ' << blpr.getCenter().y << ' ';
		fout << rect.size() << ' ' << circle.size() << ' ' << triang.size() << std::endl;
		int size = 0;
		size = rect.size();
		sf::Vector2f pos, sz;
		for (int i = 0; i < size; ++i)
		{
			sz = rect[i].getSize() * 0.5f;
			pos = rect[i].getPosition() + sz;
			fout << pos.x << ' ' << pos.y << ' ' << sz.x << ' ' << sz.y << std::endl;
		}
		size = circle.size();
		for (int i = 0; i < size; ++i)
		{
			pos = circle[i].getPosition();
			fout << pos.x << ' ' << pos.y << ' ' << circle[i].getRadius() << std::endl;
		}
		size = triang.size();
		for (int i = 0; i < size; ++i)
		{
			pos = triang[i].getPosition() - triang[i].getOrigin();
			fout << pos.x << ' ' << pos.y << ' ';
			fout << triang.begin()->getPoint(0).x << ' ' << triang.begin()->getPoint(0).y << ' ';
			fout << triang.begin()->getPoint(1).x << ' ' << triang.begin()->getPoint(1).y << ' ';
			fout << triang.begin()->getPoint(2).x << ' ' << triang.begin()->getPoint(2).y << std::endl;
		}
	}
	//----------------------------------
	//-------Загрузка спрайтов----------
	//----------------------------------
	int Ntxtr = 0, size = sprite->size();
	fout << size << ' ';
	for (int i = 0; i < size; ++i)
	{
		Ntxtr = findSprByTexture(*texture, &(sprite->at(i))) - 1;
		if (Ntxtr >= 0)
		{
			fout << Ntxtr << ' ' << (*sprite)[i].getScale().x << ' ' << (*sprite)[i].getScale().y << ' ';
			fout << (*sprite)[i].getOrigin().x << ' ' << (*sprite)[i].getOrigin().y << ' ' << (*sprite)[i].getRotation() << std::endl;
		}
	}
	//----------------------------------
	//--------Загрузка сенсора----------
	//----------------------------------
	size = sensor->size();
	fout << size << ' ';
	for (int i = 0; i < size; ++i)
	{
		fout << (*sensor)[i].getPosition().x << ' ' << (*sensor)[i].getPosition().y << ' ' << (*sensor)[i].getSize().x;
		fout << ' ' << (*sensor)[i].getSize().y << std::endl;
	}
}
void saveAB(std::vector<PrimitivBluePr>& blpr, JointBluePr& jblpr, std::ofstream& fout)
{
	sf::Vector2f posA, posB;
	int size = blpr.size();
	for (int i = 0; i < size; ++i)
		if (jblpr.primitivA == &(blpr[i]))
		{
			fout << i << ' ';
			break;
		}
	for (int i = 0; i < size; ++i)
		if (jblpr.primitivB == &(blpr[i]))
		{
			fout << i << ' ';
			break;
		}
	posA = jblpr.getPosition() - jblpr.primitivA->getPosition();
	posB = jblpr.getPosition() - jblpr.primitivB->getPosition();
	fout << posA.x << ' ' << posA.y << ' ' << posB.x << ' ' << posB.y << std::endl;
}
void Saver::save()
{
	std::cout << "Попытка создать папку " << _name << "" << std::endl;
	std::ofstream fout;
	system(("md " + _name + '0').c_str());
	fout.open((_name + "0/" + _name + ".ffts").c_str(), std::ios_base::ate);
	//==========================================
	for (int i = 0; i < CoolScrollBar::getTexturesStatic()->size(); ++i)
		system(("if /i exist " + _name + "0/img/" + _name + toString(i) + ".png () else (img/"
		+ toString(i) + ".png copy" + _name + "0/img/" + _name + toString(i) + ".png)").c_str());
	//==========================================
	int jtypes[6] = { 0, 0, 0, 0, 0, 0 };
	for (int i = 0, size = _jblpr->size(); i < size; ++i)
		jtypes[(*_jblpr)[i].type]++;
	fout << jtypes[0] + jtypes[1] << ' ' << jtypes[2] << ' ';
	fout << jtypes[3] + jtypes[4] << ' ' << jtypes[5] << ' ' << _blpr->size() << ' ';
	fout << CoolScrollBar::getTexturesStatic()->size() << std::endl;
	//==========================================
	for (int i = 0, size = _blpr->size(); i < size; ++i)
	{
		fout << i << ' ';
		saveBlPr(fout, (*_blpr)[i]);
	}
	//==========================================
	for (int i = 0, size = _jblpr->size(); i < size; ++i)
		if ((*_jblpr)[i].type == 0)
		{
			fout << 0 << ' ';
			saveAB(*_blpr, (*_jblpr)[i], fout);
			fout << (*_jblpr)[i].enableLimit;
			if ((*_jblpr)[i].enableLimit)
				fout << ' ' << (*_jblpr)[i].minl << ' ' << (*_jblpr)[i].maxl;
			fout << std::endl;
		}
	//------------------------------------------
	for (int i = 0, size = _jblpr->size(); i < size; ++i)
		if ((*_jblpr)[i].type == 1)
		{
			fout << 1 << ' ';
			saveAB(*_blpr, (*_jblpr)[i], fout);
			fout << (*_jblpr)[i].speed << ' ' << (*_jblpr)[i].force << std::endl;
		}
	//------------------------------------------
	for (int i = 0, size = _jblpr->size(); i < size; ++i)
		if ((*_jblpr)[i].type == 2)
		{
			fout << 2 << ' ';
			saveAB(*_blpr, (*_jblpr)[i], fout);
			fout << (*_jblpr)[i].speed << ' ' << (*_jblpr)[i].force << ' ' << (*_jblpr)[i].getAAngle() << ' ';
		}
	//==========================================
	for (int i = 0, size = _jblpr->size(); i < size; ++i)
		if ((*_jblpr)[i].type == 3)
		{
			fout << 3 << ' ';
			saveAB(*_blpr, (*_jblpr)[i], fout);
			fout << std::cosf((*_jblpr)[i].normal*s2dpl::GtoR) << ' ';
			fout << std::sinf((*_jblpr)[i].normal*s2dpl::GtoR) << ' ';
			fout << (*_jblpr)[i].enableLimit;
			if ((*_jblpr)[i].enableLimit)
				fout << ' ' << (*_jblpr)[i].minl << ' ' << (*_jblpr)[i].maxl;
			fout << std::endl;
		}
	//------------------------------------------
	for (int i = 0, size = _jblpr->size(); i < size; ++i)
		if ((*_jblpr)[i].type == 4)
		{
			fout << 4 << ' ';
			saveAB(*_blpr, (*_jblpr)[i], fout);
			fout << std::cosf((*_jblpr)[i].normal*s2dpl::GtoR) << ' ';
			fout << std::sinf((*_jblpr)[i].normal*s2dpl::GtoR) << ' ';
			fout << (*_jblpr)[i].speed << ' ' << (*_jblpr)[i].force << std::endl;
		}
	//------------------------------------------
	for (int i = 0, size = _jblpr->size(); i < size; ++i)
		if ((*_jblpr)[i].type == 5)
		{
			fout << 5 << ' ';
			saveAB(*_blpr, (*_jblpr)[i], fout);
			fout << std::cosf((*_jblpr)[i].normal*s2dpl::GtoR) << ' ';
			fout << std::sinf((*_jblpr)[i].normal*s2dpl::GtoR) << ' ';
			fout << (*_jblpr)[i].speed << ' ' << (*_jblpr)[i].force << ' ' << 0 << std::endl;
		}
	//------------------------------------------
	fout.close();
}
/*void Saver::saveBlPr_plus(std::ofstream& fout, PrimitivBluePr& blpr)
{
	std::vector<sf::RectangleShape>& rect = blpr.getRects();
	std::vector<sf::CircleShape>&	 circle = blpr.getCircles();
	std::vector<sf::ConvexShape>&	 triang = blpr.getTriangles();
	std::vector<SensorBpr>*			 sensor = blpr.getSensor();
	std::vector<sf::Sprite>*		 sprite = blpr.getImages();
	std::vector<sf::Texture>*		 texture = CoolScrollBar::getTexturesStatic();
	int kind = 3;
	if (rect.size() == 1 && circle.size() == 0 && triang.size() == 0) kind = 0;
	if (rect.size() == 0 && circle.size() == 1 && triang.size() == 0) kind = 1;
	if (rect.size() == 0 && circle.size() == 0 && triang.size() == 1) kind = 2;
	fout << blpr.getType() << ' ' << sensor->size() << ' ' << blpr.getMyBits() << ' ' << blpr.getColideBits() << std::endl;
	fout << blpr.getDensity() << ' ' << blpr.getFriction() << ' ' << blpr.getElasticity() << ' ' << kind << std::endl;
	if (kind == 0)
	{
		sf::Vector2f sv2(rect[0].getSize()*0.5f), pos(blpr.getPosition() + rect[0].getPosition() + sv2);
		fout << pos.x << ' ' << pos.y << ' ' << sv2.x << ' ' << sv2.y << std::endl;
	}
	if (kind == 1)
	{
		sf::Vector2f pos(blpr.getPosition() + circle[0].getPosition());
		fout << pos.x << ' ' << pos.y << ' ' << circle.begin()->getRotation() << std::endl;
	}
	if (kind == 2)
	{
		sf::Vector2f pos(blpr.getPosition() + triang[0].getPosition() - triang[0].getOrigin());
		fout << pos.x << ' ' << pos.y << ' ';
		fout << triang.begin()->getPoint(0).x << ' ' << triang.begin()->getPoint(0).y << ' ';
		fout << triang.begin()->getPoint(1).x << ' ' << triang.begin()->getPoint(1).y << ' ';
		fout << triang.begin()->getPoint(2).x << ' ' << triang.begin()->getPoint(2).y << std::endl;
	}
	if (kind == 3)
	{
		fout << blpr.getCenter().x << ' ' << blpr.getCenter().y << ' ';
		fout << rect.size() << ' ' << circle.size() << ' ' << triang.size() << std::endl;
		int size = 0;
		size = rect.size();
		sf::Vector2f pos, sz;
		for (int i = 0; i < size; ++i)
		{
			sz = rect[i].getSize() * 0.5f;
			pos = rect[i].getPosition() + sz;
			fout << pos.x << ' ' << pos.y << ' ' << sz.x << ' ' << sz.y << std::endl;
		}
		size = circle.size();
		for (int i = 0; i < size; ++i)
		{
			pos = circle[i].getPosition();
			fout << pos.x << ' ' << pos.y << ' ' << circle[i].getRadius() << std::endl;
		}
		size = triang.size();
		for (int i = 0; i < size; ++i)
		{
			pos = triang[i].getPosition() - triang[i].getOrigin();
			fout << pos.x << ' ' << pos.y << ' ';
			fout << triang.begin()->getPoint(0).x << ' ' << triang.begin()->getPoint(0).y << ' ';
			fout << triang.begin()->getPoint(1).x << ' ' << triang.begin()->getPoint(1).y << ' ';
			fout << triang.begin()->getPoint(2).x << ' ' << triang.begin()->getPoint(2).y << std::endl;
		}
	}
	//----------------------------------
	//-------Загрузка спрайтов----------
	//----------------------------------
	int Ntxtr = 0, size = sprite->size();
	fout << size << ' ';
	for (int i = 0; i < size; ++i)
	{
		Ntxtr = findSprByTexture(*texture, &(sprite->at(i))) - 1;
		if (Ntxtr >= 0)
		{
			fout << Ntxtr << ' ' << (*sprite)[i].getScale().x << ' ' << (*sprite)[i].getScale().y << ' ';
			fout << (*sprite)[i].getOrigin().x << ' ' << (*sprite)[i].getOrigin().y << ' ' << (*sprite)[i].getRotation() << std::endl;
		}
	}
	//----------------------------------
	//--------Загрузка сенсора----------
	//----------------------------------
	size = sensor->size();
	fout << size << ' ';
	for (int i = 0; i < size; ++i)
	{
		fout << (*sensor)[i].getPosition().x << ' ' << (*sensor)[i].getPosition().y << ' ' << (*sensor)[i].getSize().x;
		fout << ' ' << (*sensor)[i].getSize().y << std::endl;
	}
}*/
//---------
/*void saveAB_plus(std::vector<PrimitivBluePr>& blpr, JointBluePr& jblpr, std::ofstream& fout)
{
	sf::Vector2f posA, posB;
	int size = blpr.size();
	for (int i = 0; i < size; ++i)
		if (jblpr.primitivA == &(blpr[i]))
		{
			fout << i << ' ';
			break;
		}
	for (int i = 0; i < size; ++i)
		if (jblpr.primitivB == &(blpr[i]))
		{
			fout << i << ' ';
			break;
		}
	posA = jblpr.getPosition() - jblpr.primitivA->getPosition();
	posB = jblpr.getPosition() - jblpr.primitivB->getPosition();
	fout << posA.x << ' ' << posA.y << ' ' << posB.x << ' ' << posB.y << std::endl;
}*/
//---------
char uint16ToChar(uint16 a, int n)
{
	if (n < 4 && n > -1)
	{
		char ch = 0;
		if (n == 0)
		{
			uint16 aa = a | 0xF000;
			if (aa == 0x0000) ch == '0';
			if (aa == 0x1000) ch == '1';
			if (aa == 0x2000) ch == '2';
			if (aa == 0x3000) ch == '3';
			if (aa == 0x4000) ch == '4';
			if (aa == 0x5000) ch == '5';
			if (aa == 0x6000) ch == '6';
			if (aa == 0x7000) ch == '7';
			if (aa == 0x8000) ch == '8';
			if (aa == 0x9000) ch == '9';
			if (aa == 0xA000) ch == 'A';
			if (aa == 0xB000) ch == 'B';
			if (aa == 0xC000) ch == 'C';
			if (aa == 0xD000) ch == 'D';
			if (aa == 0xE000) ch == 'E';
			if (aa == 0xF000) ch == 'F';
		}
		if (n == 1)
		{
			uint16 aa = a | 0x0F00;
			if (aa == 0x0000) ch == '0';
			if (aa == 0x0100) ch == '1';
			if (aa == 0x0200) ch == '2';
			if (aa == 0x0300) ch == '3';
			if (aa == 0x0400) ch == '4';
			if (aa == 0x0500) ch == '5';
			if (aa == 0x0600) ch == '6';
			if (aa == 0x0700) ch == '7';
			if (aa == 0x0800) ch == '8';
			if (aa == 0x0900) ch == '9';
			if (aa == 0x0A00) ch == 'A';
			if (aa == 0x0B00) ch == 'B';
			if (aa == 0x0C00) ch == 'C';
			if (aa == 0x0D00) ch == 'D';
			if (aa == 0x0E00) ch == 'E';
			if (aa == 0x0F00) ch == 'F';
		}
		if (n == 2)
		{
			uint16 aa = a | 0x00F0;
			if (aa == 0x0000) ch == '0';
			if (aa == 0x0010) ch == '1';
			if (aa == 0x0020) ch == '2';
			if (aa == 0x0030) ch == '3';
			if (aa == 0x0040) ch == '4';
			if (aa == 0x0050) ch == '5';
			if (aa == 0x0060) ch == '6';
			if (aa == 0x0070) ch == '7';
			if (aa == 0x0080) ch == '8';
			if (aa == 0x0090) ch == '9';
			if (aa == 0x00A0) ch == 'A';
			if (aa == 0x00B0) ch == 'B';
			if (aa == 0x00C0) ch == 'C';
			if (aa == 0x00D0) ch == 'D';
			if (aa == 0x00E0) ch == 'E';
			if (aa == 0x00F0) ch == 'F';
		}
		if (n == 3)
		{
			uint16 aa = a | 0x000F;
			if (aa == 0x0000) ch == '0';
			if (aa == 0x0001) ch == '1';
			if (aa == 0x0002) ch == '2';
			if (aa == 0x0003) ch == '3';
			if (aa == 0x0004) ch == '4';
			if (aa == 0x0005) ch == '5';
			if (aa == 0x0006) ch == '6';
			if (aa == 0x0007) ch == '7';
			if (aa == 0x0008) ch == '8';
			if (aa == 0x0009) ch == '9';
			if (aa == 0x000A) ch == 'A';
			if (aa == 0x000B) ch == 'B';
			if (aa == 0x000C) ch == 'C';
			if (aa == 0x000D) ch == 'D';
			if (aa == 0x000E) ch == 'E';
			if (aa == 0x000F) ch == 'F';
		}
		return ch;
	}
}
void setQuantityOfTypes(int ptypes[], int jtypes[], std::vector<PrimitivBluePr>* blpr, std::vector<JointBluePr>* jblpr)
{
	for (PrimitivBluePr& pr : *blpr)
	{
		jtypes[0] = pr.getRects().empty();
		jtypes[1] = pr.getCircles().empty();
		jtypes[2] = pr.getTriangles().empty();
		if (pr.getRects().size() == 1 && jtypes[1] && jtypes[2])
		{
			++ptypes[0];
			continue;
		}
		if (jtypes[0] && pr.getCircles().size() == 1 && jtypes[2])
		{
			++ptypes[1];
			continue;
		}
		if (jtypes[0] && jtypes[1] && pr.getTriangles().size() == 1)
		{
			++ptypes[2];
			continue;
		}
		if (!jtypes[0] || !jtypes[1] || !jtypes[2])
		{
			++ptypes[3];
		}
	}
	jtypes[0] = 0;
	jtypes[1] = 0;
	jtypes[2] = 0;
	for (int i = 0, size = jblpr->size(); i < size; ++i)
		jtypes[(*jblpr)[i].type]++;
}
//---------
void Saver::save_plus()/*работает только если _blpr и _jblpr определены*/
{
	std::ofstream cppout, hout;
	system(("md " + _name).c_str());
	cppout.open((_name + "/" + _name + ".cpp").c_str(), std::ios_base::ate);
	hout.open((_name + "/" + _name + ".h").c_str(), std::ios_base::ate);
	//==========================================
	//-----------Записываем файл .h-------------
	//==========================================
	hout << "#ifndef " << _name << "_H" << std::endl;
	hout << "#define " << _name << "_H" << std::endl;
	hout << "#include \"../s2dpl.h\"\n" << std::endl;
	hout << "class " << _name << "\n{" << std::endl;
	hout << "private:" << std::endl;
	hout << "\tstatic b2World*\t\t\t\t_world;" << std::endl;
	hout << "\tstatic sf::RenderWindow*\t_window;" << std::endl;
	//------------------------------------------
	int ptypes[4] = { 0, 0, 0, 0 }, jtypes[6] = { 0, 0, 0, 0, 0, 0 }, picsize = CoolScrollBar::getTexturesStatic()->size();
	setQuantityOfTypes(ptypes, jtypes, _blpr, _jblpr);
	for (int i = 0; i < ptypes[0]; ++i)
		hout << "\ts2dpl::Box\t\t\t\t\t_bpart" << i << ';' << std::endl;
	for (int i = 0; i < ptypes[1]; ++i)
		hout << "\ts2dpl::Circle\t\t\t\t_cpart" << i << ';' << std::endl;
	for (int i = 0; i < ptypes[2]; ++i)
		hout << "\ts2dpl::Triangle\t\t\t\t_tpart" << i << ';' << std::endl;
	for (int i = 0; i < ptypes[3]; ++i)
		hout << "\ts2dpl::Primitiv\t\t\t\t_part" << i << ';' << std::endl;
	//------------------------------------------------
	hout << "\t//------------------------------------------" << std::endl;
	//------------------------------------------------
	for (int i = 0; i < jtypes[0]; ++i)
		hout << "\ts2dpl::RevJoint\t\t\t\t_revFreeJ" << i << ';' << std::endl;
	for (int i = 0; i < jtypes[1]; ++i)
		hout << "\ts2dpl::RevJoint\t\t\t\t_revMotJ" << i << ';' << std::endl;
	for (int i = 0; i < jtypes[2]; ++i)
		hout << "\ts2dpl::ServoRevJoint\t\t_servoRevJ" << i << ';' << std::endl;
	for (int i = 0; i < jtypes[3]; ++i)
		hout << "\ts2dpl::PrismJoint _prismFreeJ" << i << ';' << std::endl;
	for (int i = 0; i < jtypes[4]; ++i)
		hout << "\ts2dpl::PrismJoint _prismMotJ" << i << ';' << std::endl;
	for (int i = 0; i < jtypes[5]; ++i)
		hout << "\ts2dpl::ServoPrismJoint _servoPrismJ" << i << ';' << std::endl;
	//------------------------------------------------
	hout << "\t//------------------------------------------" << std::endl;
	//------------------------------------------------
	int nOfSensors = 0;
	std::for_each(_blpr->begin(), _blpr->end(), [&nOfSensors](PrimitivBluePr& blpr)
	{
		if (!blpr.getSensor()->empty())
			nOfSensors += blpr.getSensor()->size();
	});
	//------------------------------------------------
	hout << "\ts2dpl::RectSensor* _sensor[" << nOfSensors << "];" << std::endl;
	if (picsize)
	{
		hout << "\t//------------------------------------------" << std::endl;
		hout << "\tsf::Texture _texture[" << picsize << "];" << std::endl;
	}
	//================================================
	hout << "\t//==========================================" << std::endl;
	hout << "\tsf::Vector2f _position{0.f, 0.f};" << std::endl;
	hout << "\tsf::Vector2f _scale{1.f, 1.f};" << std::endl;
	hout << "\t//==========================================" << std::endl;
	//================================================
	hout << "public:" << std::endl;
	hout << "\t" << _name << "();" << std::endl;
	hout << "\t~" << _name << "();\n" << std::endl;
	hout << "\tvoid draw();" << std::endl;
	hout << "\tvoid setPosition(const sf::Vector2f& pos);" << std::endl;
	hout << "\tvoid setPosition(float x, float y);" << std::endl;
	hout << "\tconst sf::Vector2f& getPosition() const;" << std::endl;
	hout << "\tstatic void setWorld(const b2World& world);" << std::endl;
	hout << "\tstatic void setWindow(const sf::RenderWindow& window);" << std::endl;
	hout << "};" << std::endl;
	hout << "#endif";
	hout.close();
	//================================================
	//----Копирование картинок в новую диррикторию----
	//================================================
	//for (int i = 0; i < CoolScrollBar::getTexturesStatic()->size(); ++i)
	//	system(("if /i exist " + _name + "/img/" + _name + toString(i) + ".png () else (img/"
	//	+ toString(i) + ".png copy" + _name + "/img/" + _name + toString(i) + ".png)").c_str());
	//================================================
	//------------Записываем файл .cpp----------------
	//================================================
	cppout << "#include \"" << _name << '\"' << std::endl;
	cppout << "b2World*\t\t\t\t" << _name << "::_world(NULL);" << std::endl;
	cppout << "sf::RenderWindow*\t" << _name << "::_window(NULL);" << std::endl;
	cppout << std::endl;
	cppout << _name << "::" << _name << std::endl;
	cppout << "\t:" << std::endl;
	if (ptypes[0])//линейная инициализация частей-квадратов
	{
		int blsize = ptypes[0];
		int i = 0;
		int rsize, csize, tsize;
		std::for_each(_blpr->begin(), _blpr->end(), [&cppout, &blsize, &i, &rsize, &csize, &tsize](PrimitivBluePr& blpr)
		{
			rsize = blpr.getRects().size();
			csize = blpr.getCircles().size();
			tsize = blpr.getTriangles().size();
			if (rsize == 1 && (csize + tsize) == 0 && i < blsize)
			{
				cppout << "\t_bpart" << i << "(*(" << _name << "::_world), *(" << _name << "::_window),";
				cppout << " sf::Vector2f(_position.x + ";
					cppout << blpr.getPosition().x + blpr.getRects().begin()->getPosition().x + blpr.getRects().begin()->getSize().x * 0.5f << ", _position.y + ";
					cppout << blpr.getPosition().y + blpr.getRects().begin()->getPosition().y + blpr.getRects().begin()->getSize().y * 0.5f << "), ";
				cppout << "sf::Vector2f(" << blpr.getRects().begin()->getSize().x * 0.5f << " * _scale.x, " << blpr.getRects().begin()->getSize().y * 0.5f << " * _scale.y), ";
				cppout << blpr.getDensity() << ", " << blpr.getFriction() << ", " << blpr.getElasticity() << ", " << blpr.getType();
				cppout << ", 0x";
				cppout << uint16ToChar(blpr.getMyBits(), 0);
				cppout << uint16ToChar(blpr.getMyBits(), 1);
				cppout << uint16ToChar(blpr.getMyBits(), 2);
				cppout << uint16ToChar(blpr.getMyBits(), 3);
				cppout << ", 0x";
				cppout << uint16ToChar(blpr.getColideBits(), 0);
				cppout << uint16ToChar(blpr.getColideBits(), 1);
				cppout << uint16ToChar(blpr.getColideBits(), 2);
				cppout << uint16ToChar(blpr.getColideBits(), 3);
				cppout << ");" << std::endl;
				blpr.sn = i;
				blpr.st = 0;
				++i;
			}
		});
		cppout << "\t//------------------------------------------" << std::endl;
	}
	if (ptypes[1])//линейная инициализация частей-кругов
	{
		int blsize = ptypes[1];
		int i = 0;
		int rsize, csize, tsize;
		std::for_each(_blpr->begin(), _blpr->end(), [&cppout, &blsize, &i, &rsize, &csize, &tsize](PrimitivBluePr& blpr)
		{
			rsize = blpr.getRects().size();
			csize = blpr.getCircles().size();
			tsize = blpr.getTriangles().size();
			if ((rsize + tsize) == 0 && csize == 1 && i < blsize)
			{
				cppout << "\t_cpart" << i << "(*(" << _name << "::_world), *(" << _name << "::_window),";
				cppout << " sf::Vector2f(_position.x + ";
				cppout << blpr.getPosition().x + blpr.getCircles().begin()->getPosition().x << ", _position.y + ";
				cppout << blpr.getPosition().y + blpr.getCircles().begin()->getPosition().y << "), ";
				cppout << blpr.getCircles().begin()->getRadius() << " * (_scale.x+scale.y)/2.f, ";
				cppout << blpr.getDensity() << ", " << blpr.getFriction() << ", " << blpr.getElasticity() << ", " << blpr.getType();
				cppout << ", 0x";
				cppout << uint16ToChar(blpr.getMyBits(), 0);
				cppout << uint16ToChar(blpr.getMyBits(), 1);
				cppout << uint16ToChar(blpr.getMyBits(), 2);
				cppout << uint16ToChar(blpr.getMyBits(), 3);
				cppout << ", 0x";
				cppout << uint16ToChar(blpr.getColideBits(), 0);
				cppout << uint16ToChar(blpr.getColideBits(), 1);
				cppout << uint16ToChar(blpr.getColideBits(), 2);
				cppout << uint16ToChar(blpr.getColideBits(), 3);
				cppout << ");" << std::endl;
				blpr.sn = i;
				blpr.st = 1;
				++i;
			}
		});
		cppout << "\t//------------------------------------------" << std::endl;
	}
	if (ptypes[2])//линейная инициализация частей-треугольников
	{
		int blsize = ptypes[2];
		int i = 0;
		int rsize, csize, tsize;
		std::for_each(_blpr->begin(), _blpr->end(), [&cppout, &blsize, &i, &rsize, &csize, &tsize](PrimitivBluePr& blpr)
		{
			rsize = blpr.getRects().size();
			csize = blpr.getCircles().size();
			tsize = blpr.getTriangles().size();
			if ((rsize + csize) == 0 && tsize == 1 && i < blsize)
			{
				cppout << "\tsf::Vector2f vert[3] = {";
				cppout << "sf::Vector2f(" << blpr.getTriangles().begin()->getPoint(0).x << ", " << blpr.getTriangles().begin()->getPoint(0).y << "), ";
				cppout << "sf::Vector2f(" << blpr.getTriangles().begin()->getPoint(1).x << ", " << blpr.getTriangles().begin()->getPoint(1).y << "), ";
				cppout << "sf::Vector2f(" << blpr.getTriangles().begin()->getPoint(2).x << ", " << blpr.getTriangles().begin()->getPoint(2).y << ")};" << std::endl;
				cppout << "\t_tpart" << i << "(*(" << _name << "::_world), *(" << _name << "::_window),";
				cppout << " sf::Vector2f(_position.x + ";
				cppout << blpr.getPosition().x + blpr.getTriangles().begin()->getPosition().x - blpr.getTriangles().begin()->getOrigin().x << ", _position.y + ";
				cppout << blpr.getPosition().y + blpr.getTriangles().begin()->getPosition().y - blpr.getTriangles().begin()->getOrigin().y << "), ";
				cppout << "/*verti*/ sf::Vector2f(" << blpr.getTriangles().begin()->getPoint(0).x << ", " << blpr.getTriangles().begin()->getPoint(0).y << "),";
				cppout <<
				cppout <<", " << blpr.getDensity() << ", " << blpr.getFriction() << ", " << blpr.getElasticity() << ", " << blpr.getType();
				cppout << ", 0x";
				cppout << uint16ToChar(blpr.getMyBits(), 0);
				cppout << uint16ToChar(blpr.getMyBits(), 1);
				cppout << uint16ToChar(blpr.getMyBits(), 2);
				cppout << uint16ToChar(blpr.getMyBits(), 3);
				cppout << ", 0x";
				cppout << uint16ToChar(blpr.getColideBits(), 0);
				cppout << uint16ToChar(blpr.getColideBits(), 1);
				cppout << uint16ToChar(blpr.getColideBits(), 2);
				cppout << uint16ToChar(blpr.getColideBits(), 3);
				cppout << ");" << std::endl;
				blpr.sn = i;
				blpr.st = 2;
				++i;
			}
		});
		cppout << "\t//------------------------------------------" << std::endl;
	}
	if (ptypes[3])//линейная инициализация составных частей
	{
		int blsize = ptypes[3];
		int i = 0;
		int rsize, csize, tsize;
		std::for_each(_blpr->begin(), _blpr->end(), [&cppout, &blsize, &i, &rsize, &csize, &tsize](PrimitivBluePr& blpr)
		{
			rsize = blpr.getRects().size();
			csize = blpr.getCircles().size();
			tsize = blpr.getTriangles().size();
			if (!(rsize == 1 && (csize + tsize) == 0) && !(csize == 1 && (rsize + tsize) == 0) && !(tsize == 1 && (rsize + csize) == 0) && i < blsize)
			{
				cppout << "\t_part[" << i << "](*(" << _name << "::_world), *(" << _name << "::_window), ";
				cppout << "sf::Vector2f(" << blpr.getCenter().x << ", " << blpr.getCenter().y << "), ";
				cppout << blpr.getDensity() << ", " << blpr.getFriction() << ", " << blpr.getElasticity() << ", " << blpr.getType();
				cppout << ", 0x";
				cppout << uint16ToChar(blpr.getMyBits(), 0);
				cppout << uint16ToChar(blpr.getMyBits(), 1);
				cppout << uint16ToChar(blpr.getMyBits(), 2);
				cppout << uint16ToChar(blpr.getMyBits(), 3);
				cppout << ", 0x";
				cppout << uint16ToChar(blpr.getColideBits(), 0);
				cppout << uint16ToChar(blpr.getColideBits(), 1);
				cppout << uint16ToChar(blpr.getColideBits(), 2);
				cppout << uint16ToChar(blpr.getColideBits(), 3);
				cppout << ");" << std::endl;
				blpr.sn = i;
				blpr.st = 3;
				++i;
			}
		});
		cppout << "\t//==========================================" << std::endl;
	}
	//==========================================
	if (jtypes[0])
	{
		int i = 0;
		std::for_each(_jblpr->begin(), _jblpr->end(), [&cppout, &i](JointBluePr& joint)
		{
			if (joint.type == 0)
			{
				cppout << "\t_refFreeJ[" << i << "] = s2dpl::ServoRevJoint(*(" << _name << "::_world), *(" << _name << "::_window), ";
				cppout << "(s2dpl::Primitiv*)(&(_";
				if (joint.primitivA->st == 0) cppout << 'b';
				if (joint.primitivA->st == 1) cppout << 'c';
				if (joint.primitivA->st == 2) cppout << 't';
				cppout << "part[" << joint.primitivA->sn << "])), ";
				cppout << "(s2dpl::Primitiv*)(&(_";
				if (joint.primitivB->st == 0) cppout << 'b';
				if (joint.primitivB->st == 1) cppout << 'c';
				if (joint.primitivB->st == 2) cppout << 't';
				cppout << "part[" << joint.primitivB->sn << "])), ";
				cppout << "sf::Vector2f(" << joint.getPosition().x - joint.primitivA->getPosition().x << ", " << joint.getPosition().y - joint.primitivA->getPosition().y << "), ";
				cppout << "sf::Vector2f(" << joint.getPosition().x - joint.primitivB->getPosition().x << ", " << joint.getPosition().y - joint.primitivB->getPosition().y << "));" << std::endl;
				++i;
			}
		});
	}
	if (jtypes[1])
	{
		int i = 0;
		std::for_each(_jblpr->begin(), _jblpr->end(), [&cppout, &i](JointBluePr& joint)
		{
			if (joint.type == 1)
			{
				cppout << "\t_refMotJ[" << i << "](*(" << _name << "::_world), *(" << _name << "::_window), ";
				cppout << "(s2dpl::Primitiv*)(&(_";
				if (joint.primitivA->st == 0) cppout << 'b';
				if (joint.primitivA->st == 1) cppout << 'c';
				if (joint.primitivA->st == 2) cppout << 't';
				cppout << "part[" << joint.primitivA->sn << "])), ";
				cppout << "(s2dpl::Primitiv*)(&(_";
				if (joint.primitivB->st == 0) cppout << 'b';
				if (joint.primitivB->st == 1) cppout << 'c';
				if (joint.primitivB->st == 2) cppout << 't';
				cppout << "part[" << joint.primitivB->sn << "])), ";
				cppout << "sf::Vector2f(" << joint.getPosition().x - joint.primitivA->getPosition().x << ", " << joint.getPosition().y - joint.primitivA->getPosition().y << "), ";
				cppout << "sf::Vector2f(" << joint.getPosition().x - joint.primitivB->getPosition().x << ", " << joint.getPosition().y - joint.primitivB->getPosition().y << "))," << std::endl;
				++i;
			}
		});
	}
	if (jtypes[2])
	{
		int i = 0;
		std::for_each(_jblpr->begin(), _jblpr->end(), [&cppout, &i](JointBluePr& joint)
		{
			if (joint.type == 2)
			{
				cppout << "\t_servoRevJ[" << i << "](*(" << _name << "::_world), *(" << _name << "::_window), ";
				cppout << "(s2dpl::Primitiv*)(&(_";
				if (joint.primitivA->st == 0) cppout << 'b';
				if (joint.primitivA->st == 1) cppout << 'c';
				if (joint.primitivA->st == 2) cppout << 't';
				cppout << "part[" << joint.primitivA->sn << "])), (s2dpl::Primitiv*)(&(_";
				if (joint.primitivB->st == 0) cppout << 'b';
				if (joint.primitivB->st == 1) cppout << 'c';
				if (joint.primitivB->st == 2) cppout << 't';
				cppout << "part[" << joint.primitivB->sn << "])),";
				cppout << "sf::Vector2f(" << joint.getPosition().x - joint.primitivA->getPosition().x << ", " << joint.getPosition().y - joint.primitivA->getPosition().y << "), ";
				cppout << "sf::Vector2f(" << joint.getPosition().x - joint.primitivB->getPosition().x << ", " << joint.getPosition().y - joint.primitivB->getPosition().y << "))," << std::endl;
				++i;
			}
		});
	}
	//------------------------------------------
	if (jtypes[3])
	{
		int i = 0;
		std::for_each(_jblpr->begin(), _jblpr->end(), [&cppout, &i](JointBluePr& joint)
		{
			if (joint.type == 3)
			{
				cppout << "\t_prismFreeJ[" << i << "](*(" << _name << "::_world), *(" << _name << "::_window), ";
				cppout << "(s2dpl::Primitiv*)(&(_";
				if (joint.primitivA->st == 0) cppout << 'b';
				if (joint.primitivA->st == 1) cppout << 'c';
				if (joint.primitivA->st == 2) cppout << 't';
				cppout << "part[" << joint.primitivA->sn << "])), (s2dpl::Primitiv*)(&(_";
				if (joint.primitivB->st == 0) cppout << 'b';
				if (joint.primitivB->st == 1) cppout << 'c';
				if (joint.primitivB->st == 2) cppout << 't';
				cppout << "part[" << joint.primitivB->sn << "])),";
				cppout << "sf::Vector2f(" << joint.getPosition().x - joint.primitivA->getPosition().x << ", " << joint.getPosition().y - joint.primitivA->getPosition().y << "), ";
				cppout << "sf::Vector2f(" << joint.getPosition().x - joint.primitivB->getPosition().x << ", " << joint.getPosition().y - joint.primitivB->getPosition().y << "), ";
				cppout << "sf::Vector2f(" << std::cosf(joint.normal * s2dpl::GtoR) << ", " << std::sinf(joint.normal * s2dpl::GtoR) << "))," << std::endl;
				++i;
			}
		});
	}
	if (jtypes[4])
	{
		int i = 0;
		std::for_each(_jblpr->begin(), _jblpr->end(), [&cppout, &i](JointBluePr& joint)
		{
			if (joint.type == 4)
			{
				cppout << "\t_prismMotJ[" << i << "](*(" << _name << "::_world), *(" << _name << "::_window), ";
				cppout << "(s2dpl::Primitiv*)(&(_";
				if (joint.primitivA->st == 0) cppout << 'b';
				if (joint.primitivA->st == 1) cppout << 'c';
				if (joint.primitivA->st == 2) cppout << 't';
				cppout << "part[" << joint.primitivA->sn << "])), (s2dpl::Primitiv*)(&(_";
				if (joint.primitivB->st == 0) cppout << 'b';
				if (joint.primitivB->st == 1) cppout << 'c';
				if (joint.primitivB->st == 2) cppout << 't';
				cppout << "part[" << joint.primitivB->sn << "])),";
				cppout << "sf::Vector2f(" << joint.getPosition().x - joint.primitivA->getPosition().x << ", " << joint.getPosition().y - joint.primitivA->getPosition().y << "), ";
				cppout << "sf::Vector2f(" << joint.getPosition().x - joint.primitivB->getPosition().x << ", " << joint.getPosition().y - joint.primitivB->getPosition().y << "), ";
				cppout << "sf::Vector2f(" << std::cosf(joint.normal * s2dpl::GtoR) << ", " << std::sinf(joint.normal * s2dpl::GtoR) << "))," << std::endl;
				++i;
			}
		});
	}
	if (jtypes[5])
	{
		int i = 0;
		std::for_each(_jblpr->begin(), _jblpr->end(), [&cppout, &i](JointBluePr& joint)
		{
			if (joint.type == 5)
			{
				cppout << "\t_servoPrismJ[" << i << "](*(" << _name << "::_world), *(" << _name << "::_window), ";
				cppout << "(s2dpl::Primitiv*)(&(_";
				if (joint.primitivA->st == 0) cppout << 'b';
				if (joint.primitivA->st == 1) cppout << 'c';
				if (joint.primitivA->st == 2) cppout << 't';
				cppout << "part[" << joint.primitivA->sn << "])), (s2dpl::Primitiv*)(&(_";
				if (joint.primitivB->st == 0) cppout << 'b';
				if (joint.primitivB->st == 1) cppout << 'c';
				if (joint.primitivB->st == 2) cppout << 't';
				cppout << "part[" << joint.primitivB->sn << "])),";
				cppout << "sf::Vector2f(" << joint.getPosition().x - joint.primitivA->getPosition().x << ", " << joint.getPosition().y - joint.primitivA->getPosition().y << "), ";
				cppout << "sf::Vector2f(" << joint.getPosition().x - joint.primitivB->getPosition().x << ", " << joint.getPosition().y - joint.primitivB->getPosition().y << "), ";
				cppout << "sf::Vector2f(" << std::cosf(joint.normal * s2dpl::GtoR) << ", " << std::sinf(joint.normal * s2dpl::GtoR) << "))," << std::endl;
				++i;
			}
		});
	}
	//==========================================
	cppout << "{" << std::endl;
	{
		int i(0);
		int blsize = ptypes[3];
		int rsize, csize, tsize;
		std::for_each(_blpr->begin(), _blpr->end(), [&cppout, &blsize, &i, &rsize, &csize, &tsize](PrimitivBluePr& blpr)
		{
			rsize = blpr.getRects().size();
			csize = blpr.getCircles().size();
			tsize = blpr.getTriangles().size();
			if (!(rsize == 1 && (csize + tsize) == 0) && !(csize == 1 && (rsize + tsize) == 0) && !(tsize == 1 && (rsize + csize) == 0) && i < blsize)
			{
				for (sf::RectangleShape& rect : blpr.getRects())
					cppout << "\t_cpart[" << i << "].addRect(sf::Vector2f(" << rect.getPosition().x + rect.getSize().x * 0.5f << ", " << rect.getPosition().y + rect.getSize().y * 0.5f << "), sf::Vector2f(" << rect.getSize().x * 0.5f << ", " << rect.getSize().y * 0.5f << "), " << blpr.getDensity() << ", " << blpr.getFriction() << ", " << blpr.getElasticity() << ");" << std::endl;
				for (sf::CircleShape& circ : blpr.getCircles())
					cppout << "\t_cpart[" << i << "].addCirc(sf::Vector2f(" << circ.getPosition().x << ", " << circ.getPosition().y << "), " << circ.getRadius() << ");" << std::endl;
				cppout << "\t{" << std::endl;
				if (tsize > 1)
					cppout << "\t\tsf::Vector2f verticales[3];" << std::endl;
				for (sf::ConvexShape& triang : blpr.getTriangles())
				{
					if (tsize == 1)
						cppout << "\t\tsf::Vector2f verticales[3] = { sf::Vector2f(" << triang.getPoint(0).x << ", " << triang.getPoint(0).y << "), sf::Vector2f(" << triang.getPoint(1).x << ", " << triang.getPoint(1).y << "), sf::Vector2f(" << triang.getPoint(2).x << ", " << triang.getPoint(2).y << ") }); " << std::endl;
					if (tsize > 1)
					{
						cppout << "\t\tverticales[0](" << triang.getPoint(0).x << ", " << triang.getPoint(0).y << ");" << std::endl;
						cppout << "\t\tverticales[1](" << triang.getPoint(1).x << ", " << triang.getPoint(1).y << ");" << std::endl;
						cppout << "\t\tverticales[2](" << triang.getPoint(2).x << ", " << triang.getPoint(2).y << ");" << std::endl;
					}
					cppout << "\t\t_cpart[" << i << "].addTriang(sf::Vector2f(" << triang.getPosition().x - triang.getOrigin().x << ", " << triang.getPosition().y - triang.getOrigin().y << "), verticales);" << std::endl;
				}
				cppout << "\t}" << std::endl;
				++i;
			}
		});
	}
	//------------------------------------------
	{
		cppout << "//------------------------------------------" << std::endl;
		int i(0);
		std::for_each(_jblpr->begin(), _jblpr->end(), [&cppout, &i](JointBluePr& joint)
		{
			if (joint.type == 0)
			{
				if (joint.enableLimit)
					cppout << "\t_revFreeJ[" << i << "].onLimit(" << joint.minl << ", " << joint.maxl << ");" << std::endl;
				++i;
			}
		});
		i = 0;
		std::for_each(_jblpr->begin(), _jblpr->end(), [&cppout, &i](JointBluePr& joint)
		{
			if (joint.type == 1)
			{
				if (joint.enableMotor)
					cppout << "\t_revMotJ[" << i << "].onMotor(" << joint.speed << ", " << joint.force << ");" << std::endl;
				++i;
			}
		});
		i = 0;
		std::for_each(_jblpr->begin(), _jblpr->end(), [&cppout, &i](JointBluePr& joint)
		{
			if (joint.type == 2)
			{
				cppout << "\t_servoRevJ[" << i << "].setSpeedForce(" << joint.speed << ", " << joint.force << ");" << std::endl;
				cppout << "\t_servoRevJ[" << i << "].setAngle(" << joint.getAAngle() << ");" << std::endl;
				if (joint.enableLimit)
					cppout << "\t_servoRevJ[" << i << "].onLimit(" << joint.minl << ", " << joint.maxl << ");" << std::endl;
				++i;
			}
		});
		cppout << "//------------------------------------------" << std::endl;
		i = 0;
		std::for_each(_jblpr->begin(), _jblpr->end(), [&cppout, &i](JointBluePr& joint)
		{
			if (joint.type == 3)
			{
				if (joint.enableLimit)
					cppout << "\t_prismFreeJ[" << i << "].onLimit(" << joint.minl << ", " << joint.maxl << ");" << std::endl;
				++i;
			}
		});
		i = 0;
		std::for_each(_jblpr->begin(), _jblpr->end(), [&cppout, &i](JointBluePr& joint)
		{
			if (joint.type == 4)
			{
				if (joint.enableMotor)
					cppout << "\t_prismMotJ[" << i << "].onMotor(" << joint.speed << ", " << joint.force << ");" << std::endl;
				++i;
			}
		});
		i = 0;
		std::for_each(_jblpr->begin(), _jblpr->end(), [&cppout, &i](JointBluePr& joint)
		{
			if (joint.type == 5)
			{
				cppout << "\t_servoPrismJ[" << i << "].setSpeedForce(" << joint.speed << ", " << joint.force << ");" << std::endl;
				cppout << "\t_servoPrismJ[" << i << "].setDistance(0.f);" << std::endl;
				if (joint.enableLimit)
					cppout << "\t_servoPrismJ[" << i << "].onLimit(" << joint.minl << ", " << joint.maxl << ");" << std::endl;
				++i;
			}
		});
	}
	cppout << "}" << std::endl;
	cppout << '~' << _name << "::" << _name << "()" << std::endl;
	cppout << "{\n}" << std::endl;
	cppout.close();
}
Saver::~Saver()
{
}
