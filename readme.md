This is based on (https://github.com/MauriceGit/Partikel_accelleration_on_GPU) Note that this implementation does not actually do what is promises and is super broken and inconsistent.

Lessons learned:
 - We need to link to the multithreaded version of glfw (?????). Why, I do not know. Because of clang? what does it even mean for a library to be multithreaded?
 - You can just bind an array buffer to a VAO
 - you can just bind a GL_ARRAY_BUFFER instead of a GL_SHADER_STORAGE_BUFFER for a compute shader and "it just works"
 - it is actually quite trivial to read data back from the gpu with glMapbuffer(). Why it took me 5 years to understand this, I will never know. but I am glad that I know now.
 


