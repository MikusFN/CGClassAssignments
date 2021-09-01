
#include "AOBJLoader.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include "Developer/DesktopPlatform/Public/IDesktopPlatform.h"
#include "Developer/DesktopPlatform/Public/DesktopPlatformModule.h"

using namespace std;

void print_v(FV v);
void print_vt(FVT vt);
void print_vn(FVN vn);

int section_index = 0;

bool Open = true;
bool FirstTime = true;

AOBJLoader::AOBJLoader()
{
	PrimaryActorTick.bCanEverTick = true;

	mesh = CreateDefaultSubobject<UProceduralMeshComponent>(TEXT("GeneratedMesh"));
	mesh->AttachToComponent(GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);
}

// This is called when actor is spawned (at runtime or when you drop it into the world in editor)
void AOBJLoader::PostActorCreated()
{
	if (Open && !FirstTime) {
		Super::PostActorCreated();
		ReadOBJ();
		Open = false;
		FirstTime = true;
	}
	else if (FirstTime) {
		FirstTime = false;
		Open = true;
	}
}

// This is called when actor is already in level and map is opened
void AOBJLoader::PostLoad()
{
	Super::PostLoad();
	//ReadOBJ();
}


void AOBJLoader::ReadOBJ()
{
	string line;

	TArray<FString> OpenFilenames = OpenFileDialog();
	if (OpenFilenames.Num() > 0) {
		UE_LOG(LogTemp, Warning, TEXT("path: %s"), *OpenFilenames[0]);
		string PathToObj(TCHAR_TO_UTF8(*OpenFilenames[0]));
		ifstream OBJFile(PathToObj);

		getline(OBJFile, line);
		while (!OBJFile.eof()) {
			getline(OBJFile, line);
			FString FLine(line.c_str());
			UE_LOG(LogTemp, Warning, TEXT("line: %s"), *FLine);

			stringstream buffer(line);
			string value;

			while (getline(buffer, value, ' ')) {

				if (value.size() == 1) {
					switch (value.at(0)) {
					case 'v':
						FV v = FV();

						getline(buffer, value, ' ');
						v.x = stod(value);
						getline(buffer, value, ' ');
						v.y = stod(value);
						getline(buffer, value, ' ');
						v.z = stod(value);

						print_v(v);
						VArray.Add(v);

						break;
					case 'f':
						while (!buffer.eof()) {
							getline(buffer, value, ' ');

							FString f_line(value.c_str());
							UE_LOG(LogTemp, Warning, TEXT("f: %s"), *f_line);

							stringstream f_buffer(value);

							string f_value;
							FF f = FF();

							getline(f_buffer, f_value, '/');
							f.v = VArray[stoi(f_value) - 1];
							UE_LOG(LogTemp, Warning, TEXT("fv: %f %f %f"), f.v.x, f.v.y, f.v.z);
							getline(f_buffer, f_value, '/');
							f.vt = VTArray[stoi(f_value) - 1];
							getline(f_buffer, f_value, '/');
							f.vn = VNArray[stoi(f_value) - 1];

							FArray.Add(f);
						}

						CreateFace(FArray);
						FArray.Empty();
						section_index++;
						break;
					default:
						break;
					}
				}
				else {
					switch (value.at(1)) {
					case 't':
						FVT vt = FVT();

						getline(buffer, value, ' ');
						vt.u = stod(value);
						getline(buffer, value, ' ');
						vt.v = stod(value);

						print_vt(vt);
						VTArray.Add(vt);

						break;
					case 'n':
						FVN vn = FVN();

						getline(buffer, value, ' ');
						vn.nx = stod(value);
						getline(buffer, value, ' ');
						vn.ny = stod(value);
						getline(buffer, value, ' ');
						vn.nz = stod(value);

						print_vn(vn);
						VNArray.Add(vn);

						break;
					default:
						break;
					}
				}
			}
		}
		OBJFile.close();
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("path null"));
	}

	VArray.Empty();
	VTArray.Empty();
	VNArray.Empty();
	FArray.Empty();
}

void AOBJLoader::CreateFace(TArray<FF> F_Array) {
	UE_LOG(LogTemp, Warning, TEXT("Creating FACE %d."), section_index);
	int i = 0;
	for (auto& f : F_Array)
	{		
		vertices.Add(FVector(f.v.x, f.v.y, f.v.z));
		uvs.Add(FVector2D(f.vt.u, f.vt.v));
		normals.Add(FVector(f.vn.nx, f.vn.ny, f.vn.nz));
		//triangles.Add(i);

		i++;
	}
	triangles.Add(2);
	triangles.Add(1);
	triangles.Add(0);
	triangles.Add(0);
	triangles.Add(3);
	triangles.Add(2);

	vertexColors.Init(FLinearColor(0.0f, 0.0f, 0.0f, 1.0f), i+2);
	tangents.Init(FProcMeshTangent(1.0f, 1.0f, 1.0f), i+2);

	mesh->CreateMeshSection_LinearColor(section_index, vertices, triangles, normals, uvs, vertexColors, tangents, true);

	ClearMeshData();
}

void AOBJLoader::ClearMeshData()
{
	vertices.Empty();
	triangles.Empty();
	uvs.Empty();
	normals.Empty();
	vertexColors.Empty();
	tangents.Empty();
}

TArray<FString> AOBJLoader::OpenFileDialog() {
	IDesktopPlatform* DesktopPlatform = FDesktopPlatformModule::Get();
	TArray<FString> OpenFilenames;
	if (DesktopPlatform)
	{
		//Opening the file picker!
		uint32 SelectionFlag = 0; //A value of 0 represents single file selection while a value of 1 represents multiple file selection
		DesktopPlatform->OpenFileDialog(nullptr, FString("Choose OBJ File"), FPaths::ProjectDir(), FString(""), FString("OBJ Files|*.obj"), EFileDialogFlags::None, OpenFilenames);
	}

	return OpenFilenames;
}


// DEBUG Functions
void print_v(FV v) {
	UE_LOG(LogTemp, Warning, TEXT("v: (%f, %f, %f)"), v.x, v.y, v.z);
}

void print_vt(FVT vt) {
	UE_LOG(LogTemp, Warning, TEXT("vt: (%f, %f)"), vt.u, vt.v);
}

void print_vn(FVN vn) {
	UE_LOG(LogTemp, Warning, TEXT("vn: (%f, %f, %f)"), vn.nx, vn.ny, vn.nz);
}