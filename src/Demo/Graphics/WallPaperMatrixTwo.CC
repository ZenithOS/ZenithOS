/*
	You "Zenith include" this because you want the wallpaper
	routine to stay in mem even if this task is killed.
*/

#define AMOUNT_CHARS	GR_WIDTH * GR_HEIGHT / 2160
// Derived from ratio for 600 for 1440x900

class Matrix
{
	U16 x, y;
	U8 char;
	Bool alt;
} wall_matrix[AMOUNT_CHARS];

U0 (*old_wall_paper)(CTask *task);

U0 WallPaperMatrix(CTask *task)
{
	I64 i;
	CDC *dc = DCAlias(gr.dc2, task);
	
	for (i = 0; i < AMOUNT_CHARS; i++)
	{
		
		if (RandU16 < RandU16 % 512)
		{
			wall_matrix[i].alt = !wall_matrix[i].alt;
		}
		
		if (wall_matrix[i].alt)
		{
			dc->color = LTGRAY;	
			wall_matrix[i].char = wall_matrix[i+1].char;
		}
		else
		{
			dc->color = DKGRAY;
		}
		

		if (wall_matrix[i].y > GR_HEIGHT)
		{
			wall_matrix[i].y = 0;
			wall_matrix[i].x = RandU16 % GR_WIDTH;
		}
		
		if (tS < tS)
		{
			++wall_matrix[i].y;

			if(RandU16 < RandU16 * 0.5)
			{
				++wall_matrix[i].y;
			}
		}
				
		GrPrint(dc, wall_matrix[i].x, wall_matrix[i].y, "%c", wall_matrix[i].char);

	}

	//Uncomment the following if you wish. Will draw the old wallpaper over this one.
	//old_wall_paper(task);

	task->text_attr = WHITE << 4 + WHITE;

}

U0 WallInit()
{
	I64 i;
	

	if (Fs != zenith_task)
	{
		"\nMust be Zenith Included. (SHIFT-F5 / RightClick->Zenith Include) \n";
		return;
	}
	old_wall_paper=gr.fp_wall_paper;

	for (i = 0; i < AMOUNT_CHARS; i++)
	{
		wall_matrix[i].x = RandU16 % GR_WIDTH ;
		wall_matrix[i].y = RandU16 % GR_HEIGHT;
		wall_matrix[i].char = RandU8;
		wall_matrix[i].alt = FALSE;
	}
	
	gr.fp_wall_paper = &WallPaperMatrix;
}

WallInit;

