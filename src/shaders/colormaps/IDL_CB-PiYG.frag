R"(float colormap_red(float x) {
	if (x < 0.09843078255653381) {
		return 5.57627692307694E+02 * x + 1.42135384615385E+02;
	} else if (x < 0.4093809425830841) {
		return ((-4.21748915649019E+02 * x + 1.28054196831998E+01) * x + 2.64504106766935E+02) * x + 1.71265909327078E+02;
	} else if (x < 0.5037343473981705) {
		return -6.54538461538185E+01 * x + 2.79554615384612E+02;
	} else if (x < 0.5982368290424347) {
		return -1.66852258852308E+02 * x + 3.30632478632496E+02;
	} else {
		return ((1.82001891024969E+03 * x - 4.20447326861499E+03) * x + 2.68838861198902E+03) * x - 2.62418693972160E+02;
	}
}

float colormap_green(float x) {
	if (x < 0.101902037858963) {
		return 2.72322735042735E+02 * x + 5.21367521367536E-01;
	} else if (x < 0.5059849917888641) {
		return ((6.81035433115437E+02 * x - 1.71408042362240E+03) * x + 1.36671536460816E+03) * x - 9.39210546594673E+01;
	} else if (x < 0.5954320132732391) {
		return -2.72768472906136E+01 * x + 2.60800985221660E+02;
	} else {
		return ((1.09164194296742E+03 * x - 3.01508808799416E+03) * x + 2.33004497173996E+03) * x - 3.04306745740377E+02;
	}
}

float colormap_blue(float x) {
	if (x < 0.5011215507984161) {
		return (((((-3.44764954376220E+04 * x + 6.98813026428223E+04) * x - 4.87748659515380E+04) * x + 1.31832279253005E+04) * x - 1.26691288614273E+03) * x + 4.73465709444135E+02) * x + 8.21916531938477E+01;
	} else if (x < 0.5958432303492089) {
		return -3.80379731379794E+02 * x + 4.37472934472961E+02;
	} else if (x < 0.790071576833725) {
		return -7.13383710407293E+02 * x + 6.35891101055846E+02;
	} else {
		return (1.19760697610430E+03 * x - 2.36001183205723E+03) * x + 1.18928322234544E+03;
	}
}

vec4 colormap(float x) {
	float r = clamp(colormap_red(x) / 255.0, 0.0, 1.0);
	float g = clamp(colormap_green(x) / 255.0, 0.0, 1.0);
	float b = clamp(colormap_blue(x) / 255.0, 0.0, 1.0);
	return vec4(r, g, b, 1.0);
}
)"