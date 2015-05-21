﻿#ifndef _SAMPLING_H_
#define _SAMPLING_H_

namespace edubpt {

// cosθ/πに比例
// 引数は両方正規化しておく
inline double sample_hemisphere_pdf_omega(const Vec &normal, const Vec &dir) {
	return std::max(dot(normal, dir), 0.0) / kPI;
}
Vec sample_hemisphere_cos_term(const Vec &normal, Random *rnd, double *pdf_omega) {
	Vec w = normal, u, v;
	if (fabs(w.x) > kEPS) // ベクトルwと直交するベクトルを作る。w.xが0に近い場合とそうでない場合とで使うベクトルを変える。
		u = normalize(cross(Vec(0.0, 1.0, 0.0), w));
	else
		u = normalize(cross(Vec(1.0, 0.0, 0.0), w));
	v = cross(w, u);
	// コサイン項を使った重点的サンプリング
	const double r1 = 2 * kPI * rnd->next01();
	const double r2 = rnd->next01(), r2s = sqrt(r2);
	Vec dir = normalize((
		u * cos(r1) * r2s +
		v * sin(r1) * r2s +
		w * sqrt(1.0 - r2)));

	*pdf_omega = sample_hemisphere_pdf_omega(normal, dir);

	return dir;
}

// 半径Rの球面上から一点をサンプリング
inline double sample_sphere_pdf_A(const double R) {
	return 1.0 / (4.0 * kPI * R * R);
}
Vec sample_sphere(const double R, Random *rnd, double *pdf_A) {
	const double z = rnd->next01() * 2.0 - 1.0;
	const double sz = sqrt(1 - z*z);
	const double phi = rnd->next01() * 2.0 * kPI;

	*pdf_A = sample_sphere_pdf_A(R);

	return R * Vec(sz * cos(phi), sz * sin(phi), z);
}

// ロシアンルーレットの確率計算関数
// 局所的な情報に基づいて決定する
double russian_roulette(const Sphere &sphere) {
	return sphere.emission.length_squared() > 0 ? 1.0 : std::max(sphere.color.x, std::max(sphere.color.y, sphere.color.z));
}

// ガラス面で、反射する確率（1 - reflection_probabilityが屈折する確率）
const double reflection_probability = 0.5;

};

#endif
