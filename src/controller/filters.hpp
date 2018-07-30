class MoogFilter {
public:
  void clear();
  void setType(int t) {
    type = t;
  }
  void setSamplerate(float r) {
    sample_rate = r;
  }
  void setCoefficients(float f, float r);
  void process(float *input, float *output, int samples);

private:
  float f, pc, q;
  float bf0, bf1, bf2, bf3, bf4;
  float t1, t2;

  int type = 0;
  float sample_rate;
};
