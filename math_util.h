#ifndef MATH_UTIL_H
#define MATH_UTIL_H


double leftRiemannSum(double func(double), const double start, const double end, const int n) {

	const double deltaX = (end - start) / (double)n;

	double sum = 0.0;

	for (int i = 0; i < n; i++) {
		double x = start + (deltaX * (double)i);
		double y = func(x);
		sum += y;
	}

	return sum * deltaX;
}


double rightRiemannSum(double func(double), const double start, const double end, const int n) {
	const double deltaX = (end - start) / (double)n;

	double sum = 0.0;

	for (int i = 1; i <= n; i++) {
		double x = start + (deltaX * (double)i);
		double y = func(x);
		sum += y;
	}

	return sum * deltaX;
}


double riemannSum(double func(double), const double start, const double end, const int n) {
	const double deltaX = (end - start) / (double)n;

	double sum = 0.0;

	for (int i = 1; i < n; i++) {
		double x = start + (deltaX * (double)i);
		double y = func(x);
		sum += y;
	}

	sum = sum * deltaX;

	sum += func(start) * deltaX * 0.5;
	sum += func(end) * deltaX * 0.5;

	return sum;
}

#endif // !MATH_UTIL_H