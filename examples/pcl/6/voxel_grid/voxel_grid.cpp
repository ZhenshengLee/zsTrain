#include <iostream>
#include <pcl/io/pcd_io.h>
#include <pcl/point_types.h>
#include <pcl/filters/voxel_grid.h>
int main(int argc, char** argv)
{
    pcl::PCLPointCloud2::Ptr cloud(new pcl::PCLPointCloud2());
    pcl::PCLPointCloud2::Ptr cloud_filtered(new pcl::PCLPointCloud2());
    // 填入点云数据
    pcl::PCDReader reader;
    // 把路径改为自己存放文件的路径
    reader.read("/home/zs/Documents/zsCode/zsTrain/examples/pcl/6/voxel_grid/table_scene_lms400.pcd", *cloud);  // 记住要事先下载这个数据集！
    std::cerr << "PointCloud before filtering: " << cloud->width * cloud->height << " data points ("
              << pcl::getFieldsList(*cloud) << ").";
    // 创建滤波器对象
    pcl::VoxelGrid<pcl::PCLPointCloud2> sor;
    sor.setInputCloud(cloud);
    sor.setLeafSize(0.01f, 0.01f, 0.01f);
    sor.filter(*cloud_filtered);
    std::cerr << "PointCloud after filtering: " << cloud_filtered->width * cloud_filtered->height << " data points ("
              << pcl::getFieldsList(*cloud_filtered) << ").";
    pcl::PCDWriter writer;
    writer.write("2f.pcd", *cloud_filtered, Eigen::Vector4f::Zero(), Eigen::Quaternionf::Identity(), false);
    return (0);
}
