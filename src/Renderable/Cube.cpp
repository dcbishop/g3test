Cube::Cube() {
   pos = glm::vec3(0.0, 0.0, 0.0);
   GLfloat p = CUBE_SIZE / 2.0f;
   GLfloat n = -halfsize;
   
   glm::vec3 rtf(p, p, p);
   glm::vec3 rtb(p, p, n);
   glm::vec3 rbf(p, n, p);
   glm::vec3 rbb(p, n, n);
   glm::vec3 ltf(n, p, p);
   glm::vec3 ltb(n, p, n);
   glm::vec3 lbf(n, n, p);
   glm::vec3 lbb(n, n, n);
   
   vector<glm::vec3> cube({ltf, rtf, tbf});
}
