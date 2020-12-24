/*
	You "Zenith include" this because you want the wallpaper
	routine to stay in mem even if this task is killed.
*/

#define NUM_STARS	GR_WIDTH * GR_HEIGHT / 2160
//#define NUM_STARS GR_WIDTH * GR_HEIGHT / 512
// Derived from ratio for 600 for 1440x900

class Star
{
	U16 x, y, z;
	U8 char;

} wall_stars[NUM_STARS];

U0 (*old_wall_paper)(CTask *task);

U0 WallPaperStars(CTask *task)
{
	I64 i;
	CDC *dc = DCAlias(gr.dc2, task);
	
	dc->color = RED;
	
	F64 t0;
	t0 = tS;
	

	for (i = 0; i < NUM_STARS; i++)
	{
		//GrLine(dc, wall_stars[i].x, wall_stars[i].y, wall_stars[i].x, wall_stars[i].y + 10);
		//dc->color = i >> 4;
		
		GrPrint(dc, wall_stars[i].x, wall_stars[i].y + (wall_stars[i].z * Rand), "%c", wall_stars[i].char + 1);
		

		if(RandU16 < t0 * 100)
		{	
			++wall_stars[i].y;
		}
			
		//++wall_stars[i].y;
	
		
		if (RandU16 * 32 < RandU16)
		{
			wall_stars[i].char = RandU8;
			dc->color = GREEN;	
		}
		
		if (RandU16 * 512 < RandU16)
		{
			dc->color = PURPLE;
		}


		if (wall_stars[i].y > GR_HEIGHT)
		{
			wall_stars[i].y = 0;
			wall_stars[i].x = RandU16 % GR_WIDTH;
		}
		
		//if (++wall_stars[i].x > GR_WIDTH){

		//	wall_stars[i].y = RandU16 % GR_HEIGHT;
		//	wall_stars[i].x = 0;
		//}
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

	for (i = 0; i < NUM_STARS; i++)
	{
		wall_stars[i].x = RandU16 % GR_WIDTH ;
		wall_stars[i].y = RandU16 % GR_HEIGHT;
		wall_stars[i].z = Rand;
		wall_stars[i].char = Rand;
	}
	
	gr.fp_wall_paper = &WallPaperStars;
}

WallInit;

